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
   * - Read a deck
     - ``reader.readModel(path)``
     - ``oo_reader.read_model(path)``
   * - Count node rows
     - ``query.rowCount()``
     - ``len(table)``
   * - Save a model
     - ``deck.writeArchive(path)``
     - ``deck.write_archive(path)``

JavaScript and TypeScript
-------------------------

Load the built package from ``build/wasm/dist/index.js``. The declarations below describe its public interface.

.. literalinclude:: ../wasm/js/index.d.ts
   :language: typescript
   :linenos:

.. _native-python-api:

Python
------

Import ``read_model(path, *, strict=True)`` from ``oo_reader``. It returns a ``Deck``.

* Inspect ``deck.card_counts``, ``deck.diagnostics`` and ``deck.card_types(group)``.
* Select columns with ``deck.card_table(name, columns)`` or run ``deck.query(name, **arguments)``.
  Both return a ``Table`` with ``columns``, a row count via ``len(table)`` and an Arrow capsule.
* Edit a copy with ``deck.copy()`` and ``set_card_value(card, id, field, value)``.
  Apply design variables with ``deck.with_design_point(ids, values)`` to get a new deck.
* Save to text with ``deck.write_model(path)`` or to HDF5 with ``deck.write_archive(path)``.

See :doc:`python` for paired examples and installation details. The public
`Python module <https://github.com/jcdulas/O_o_Reader/blob/main/python/oo_reader/__init__.py>`_ and
`native bindings <https://github.com/jcdulas/O_o_Reader/blob/main/python/bindings.cpp>`_ define the available calls.

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

ArchiveWriter.hpp
~~~~~~~~~~~~~~~~~

.. literalinclude:: ../include/oor/results/archive/ArchiveWriter.hpp
   :language: cpp
   :linenos:

ArchiveResultFile.hpp
~~~~~~~~~~~~~~~~~~~~~

.. literalinclude:: ../include/oor/results/archive/ArchiveResultFile.hpp
   :language: cpp
   :linenos:

ArchiveModel.hpp
~~~~~~~~~~~~~~~~

.. literalinclude:: ../include/oor/results/archive/ArchiveModel.hpp
   :language: cpp
   :linenos:
