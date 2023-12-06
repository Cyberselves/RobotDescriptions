^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package moose_control
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

0.1.2 (2022-03-07)
------------------
* Move rosparam load outside the joy_teleop ns. (`#5 <https://github.com/moose-cpr/moose/issues/5>`_)
  * Move the joy parameters outside the joy_teleop ns to avoid duplicating the namespace. Resolves https://github.com/moose-cpr/moose/issues/4
  * Move the rosparam load back into the teleop namespace, remove the namespace from the yaml file
* Contributors: Chris I-B

0.1.1 (2021-03-09)
------------------
* Expose MOOSE_JOY_DEV and MOOSE_JOY_TELEOP environment variables.  Enable the joy node's messages to be received by twist_mux with the same priority as Warthog.
* Contributors: Chris Iverach-Brereton

0.1.0 (2019-12-11)
------------------
* Updated collisions,
* Made the generator optional
* Moved interactive markers to manned control and removed joy
* Added wheels to URDF.
* Initial commit for Moose.
* Contributors: Dave Niewinski, Tony Baltovski
