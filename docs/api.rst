API reference
=============

The table maps the most common operations across both packages. For Python signatures, see :ref:`native-python-api`.
The TypeScript declarations and C++ headers below are included directly from the source tree.

For a runnable example, start with :doc:`getting-started`. The module guides explain implementation details.

.. list-table::
   :header-rows: 1

   * - Operation
     - JavaScript / WebAssembly
     - Python / native C++
   * - Create an empty model
     - ``reader.createModel()``
     - ``oo_model.create_model()``
   * - Add a homogeneous batch
     - ``deck.addCardBatch(type, columns)``
     - ``deck.add_card_batch(type, columns)``
   * - Validate references
     - ``deck.checkReferences()``
     - ``deck.check_references()``
   * - Read a deck with a file adapter
     - ``reader.readModel(path)``
     - ``oo_model.read_model(path)``
   * - Count node rows
     - ``query.rowCount()``
     - ``len(table)``
   * - Save a model with the archive adapter
     - ``deck.writeArchive(path)``
     - ``deck.write_archive(path)``

JavaScript and TypeScript
-------------------------

Load the built package from ``build/wasm/dist/index.js``. The declarations below describe its public interface.

.. literalinclude:: ../wasm/js/index.d.ts
   :end-before: // Compatibility exports
   :language: typescript
   :linenos:

.. _native-python-api:

Python
------

Call ``oo_model.create_model()`` to construct an in-memory ``Deck``. The optional file adapters also expose ``read_model(path, *, strict=True)``.

* Create a deck with ``create_model()``, select the solution with ``deck.set_solution(name)`` and set the case
  commands with ``deck.set_case_control(records)``. Each record provides a name and a sequence of string fields.
* Insert a card with ``deck.add_card(type, fields, *, form="", comment=None)`` or insert several types atomically with
  ``deck.add_cards(records)``. Insert scalar or NumPy columns with ``deck.add_card_batch(type, columns, *, count=None, form="")``.
  Call ``deck.apply_defaults()`` and ``deck.check_references()`` before handing the model to a solver.
* Inspect ``deck.card_counts``, ``deck.diagnostics`` and ``deck.card_types(group)``.
* Select columns with ``deck.card_table(name, columns)`` or run ``deck.query(name, **arguments)``.
  Both return a ``Table`` with ``columns``, a row count via ``len(table)`` and an Arrow capsule.
* Edit a copy with ``deck.copy()`` and ``set_card_value(card, id, field, value)``.
  Apply design variables with ``deck.with_design_point(ids, values)`` to get a new deck.
* Save to text with ``deck.write_model(path)`` or to HDF5 with ``deck.write_archive(path)``.

See :doc:`python` for paired examples and installation details. The public
`Python module <https://github.com/jcdulas/O_o_Model/blob/main/python/oo_model/__init__.py>`_ and
`native bindings <https://github.com/jcdulas/O_o_Model/blob/main/python/bindings.cpp>`_ define the available calls.

C++ entry points
----------------

Deck.hpp
~~~~~~~~

.. literalinclude:: ../include/oor/api/Deck.hpp
   :language: cpp
   :linenos:

CardTables.hpp
~~~~~~~~~~~~~~

.. literalinclude:: ../include/oor/api/CardTables.hpp
   :language: cpp
   :linenos:

CardEdits.hpp
~~~~~~~~~~~~~

.. literalinclude:: ../include/oor/api/CardEdits.hpp
   :language: cpp
   :linenos:

ControlEdits.hpp
~~~~~~~~~~~~~~~~

.. literalinclude:: ../include/oor/api/ControlEdits.hpp
   :language: cpp
   :linenos:

Queries.hpp
~~~~~~~~~~~

.. literalinclude:: ../include/oor/api/Queries.hpp
   :language: cpp
   :linenos:

Results.hpp
~~~~~~~~~~~

.. literalinclude:: ../include/oor/api/Results.hpp
   :language: cpp
   :linenos:

Design.hpp
~~~~~~~~~~

.. literalinclude:: ../include/oor/api/Design.hpp
   :language: cpp
   :linenos:

Native archive interfaces
-------------------------

The :doc:`archive-format` guide specifies archive version 4 and native model schema 1. These lower-level interfaces
write a model with optional result tables, stream result tables into an archive, and load native model data independently.
The ``Deck`` and ``Results`` facade above also exposes these operations to application code.

The C++ declarations for the archive adapter are maintained in its repository:

* `ArchiveWriter.hpp <https://github.com/jcdulas/O_o_OOH5/blob/main/include/oor/results/archive/ArchiveWriter.hpp>`_
* `ArchiveResultFile.hpp <https://github.com/jcdulas/O_o_OOH5/blob/main/include/oor/results/archive/ArchiveResultFile.hpp>`_
* `ArchiveModel.hpp <https://github.com/jcdulas/O_o_OOH5/blob/main/include/oor/results/archive/ArchiveModel.hpp>`_

.. literalinclude:: ../include/oor/results/writers/ArchiveWriteOptions.hpp
   :language: cpp
