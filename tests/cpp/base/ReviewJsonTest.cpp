// The numbers of a JSON text are read the same way whatever the locale of the program: the arguments of a query
// arrive as JSON from a host program, which may have set a locale that writes a decimal comma.
#include "oor/base/errors/Errors.hpp"
#include "oor/base/text/Json.hpp"

#include <catch2/catch_test_macros.hpp>

#include <clocale>
#include <string>

using namespace oor;

namespace
{

// A locale that writes a decimal comma, set while the object lives when the machine has one (isSet()); the locale of
// the program is put back at the end, also when a check stops the test.
class DecimalCommaLocale
{
public:
    DecimalCommaLocale() : m_before(std::setlocale(LC_NUMERIC, nullptr))
    {
        for (const char* name :
             {"fr_FR.UTF-8", "fr_FR", "French_France.1252", "fr-FR", "de_DE.UTF-8", "German_Germany.1252"})
            if (std::setlocale(LC_NUMERIC, name) != nullptr && *std::localeconv()->decimal_point == ',')
            {
                m_isSet = true;
                return;
            }
    }
    DecimalCommaLocale(const DecimalCommaLocale&) = delete;
    DecimalCommaLocale& operator=(const DecimalCommaLocale&) = delete;
    ~DecimalCommaLocale() { std::setlocale(LC_NUMERIC, m_before.c_str()); }

    [[nodiscard]] bool isSet() const noexcept { return m_isSet; }

private:
    std::string m_before;
    bool m_isSet = false;
};

void checkNumbers()
{
    const base::JsonValue document =
        base::JsonValue::parse(R"({"tolerance": 0.5, "list": [1.25, -2e-3, 3], "big": 1E3, "plus": [+5]})");
    CHECK(document.member("tolerance")->asNumber("tolerance") == 0.5);
    const std::vector<double>& list = document.member("list")->asNumbers("list");
    REQUIRE(list.size() == 3);
    CHECK(list[0] == 1.25);
    CHECK(list[1] == -0.002);
    CHECK(list[2] == 3.0);
    CHECK(document.member("big")->asNumber("big") == 1000.0);
    // a leading '+' is not JSON, but was read before and still is
    CHECK(document.member("plus")->asArray("plus").front().asNumber("plus") == 5.0);
}

} // namespace

TEST_CASE("JSON numbers are read in the default locale", "[base][json][review]")
{
    checkNumbers();
}

TEST_CASE("JSON numbers do not follow a locale with a decimal comma", "[base][json][review]")
{
    const DecimalCommaLocale locale;
    INFO("a decimal-comma locale was " << (locale.isSet() ? "set" : "not available on this machine"));
    checkNumbers();
}

TEST_CASE("a text that is not a JSON number is refused with its text", "[base][json][review]")
{
    CHECK_THROWS_AS(base::JsonValue::parse("1.2.3"), base::UsageError);
    CHECK_THROWS_AS(base::JsonValue::parse("[0,5e]"), base::UsageError);
    CHECK_THROWS_AS(base::JsonValue::parse("{\"a\": 1e999}"), base::UsageError); // outside the range of a number
    CHECK_THROWS_AS(base::JsonValue::parse("+"), base::UsageError);
}
