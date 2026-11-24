"""Compatibility import for applications using the former package name."""
from oo_model import Deck, Diagnostic, Table, card_columns, create_model, read_model

__all__ = ["Deck", "Diagnostic", "Table", "card_columns", "create_model", "read_model"]
