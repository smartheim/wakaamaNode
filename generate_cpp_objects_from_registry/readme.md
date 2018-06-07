# XSL Transformation from lwm2m object registry to WakaamaNode cpp objects

The java program in this directory executes
the XSL transformation in _res/transform/transform.xsl_ for all
xml input files in _res/lwm2m_object_registry_ which have been successfully validated against the _res/schema/LWM2M.xsd_ schema.
Output files are written to an _out_ directory.

The program tries to update the input files before transforming them if the "-u" command line parameter is given.

## Arguments

* -dv,--disable-validation   Disable the validation of downloaded files
* -o,--output <arg>          output file path (default is 'out')
* -r,--res <arg>             resource file path, with schema and transform subdirectory (default is 'res')
* -u,--update                update OMA registry files (default is false)
* -url,--update-url <arg>    OMA registry url (default is http://www.openmobilealliance.org/wp/DDF.xml)

## Input files

All res/lwm2m_object_registry files are downloaded from
[[http://www.openmobilealliance.org/wp/DDF.xml]] and [[http://www.openmobilealliance.org/wp/OMNA/LwM2M/Common.xml]].
The schema validation file is _res/schema/LWM2M.xsd_.

## Output files

Output files are written to the directory called "out" in the working directory.

## Build/Run

Build with `gradle build`. Run with `gradle run`.
