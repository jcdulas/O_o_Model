#pragma once

#include "oor/api/Deck.hpp"

#include <pybind11/pybind11.h>

void bindModelBuilder(pybind11::class_<oor::api::Deck, std::shared_ptr<oor::api::Deck>>& deck);
