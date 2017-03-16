# cad2xls Python Script
This is a Python script for extracting parameter values from an Assembly (STEP)
file.

The main **GetParameters** class allows the user to create new instances in order to handle
**STEP** files. The CAD file path has to be passed using the **filePath** parameter
belongs to the class **GetParameters**

By default, the class constructor creates an instance using a default path for the
CAD model, this value must be changed modifying the variable **filePath** belongs to
the instance your are dealing with.

---

## Dependencies
* **FreeCAD:** https://www.freecadweb.org/
* **xlwt:** https://github.com/python-excel/xlwt
