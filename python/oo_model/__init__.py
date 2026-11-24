"""Build, edit and query O_o models and expose their native tables through the Arrow C Data Interface."""
from os import fsdecode

from ._native import Deck, Diagnostic, Table, card_columns, create_model, read_model as _read_model


def read_model(path, *, strict=True):
    """Read a local .oos or .ooh5 file. Relative includes follow the model file."""
    return _read_model(fsdecode(path), strict)


__all__ = ["Deck", "Diagnostic", "Table", "card_columns", "create_model", "read_model"]
