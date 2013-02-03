AeroTelemetry

This is the ground-based software for AeroTelemetry. It is built on a plugin principle, allowing
the developers to use well-defined interfaces to external code. It is CRITICAL that the interfaces
to these plugins do not break existing functionality at any commit.

The main code is licensed under GPLv3. You are encouraged, but not required to share any new plugins you write.

This code relies on VTK-5.8 and openNURBS-5 (available from http://download.rhino3d.com/openNURBS/5.0/release/download).
CAD geometry in openNURBS (3dm) format is used for scenery and model geometries.
