<h1 align="center">
    TELEMETRY, TRACKING AND COMMAND
    <br>
</h1>

<h4 align="center">Telemetry, Tracking and Command module designed and developed by SpaceLab.</h4>

<p align="center">
	<a href="https://github.com/spacelab-ufsc/spacelab#versioning">
		<img src="https://img.shields.io/badge/status-in--orbit%20validated-blue?style=for-the-badge">
	</a>
	<a href="https://github.com/spacelab-ufsc/ttc/releases">
		<img alt="GitHub release (latest by date)" src="https://img.shields.io/github/v/release/spacelab-ufsc/ttc?style=for-the-badge">
	</a>
	<a href="https://github.com/spacelab-ufsc/ttc/releases">
		<img alt="GitHub commits since latest release (by date)" src="https://img.shields.io/github/commits-since/spacelab-ufsc/ttc/latest?style=for-the-badge">
	</a>
	<a href="https://github.com/spacelab-ufsc/ttc/commits/master">
		<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/spacelab-ufsc/ttc?style=for-the-badge">
	</a>
	<a href="https://github.com/spacelab-ufsc/ttc/issues">
		<img alt="GitHub issues" src="https://img.shields.io/github/issues/spacelab-ufsc/ttc?style=for-the-badge">
	</a>
	<a href="https://github.com/spacelab-ufsc/ttc/graphs/contributors">
		<img alt="GitHub contributors" src="https://img.shields.io/github/contributors/spacelab-ufsc/ttc?color=yellow&style=for-the-badge">
	</a>
	<a href="#license">
		<img src="https://img.shields.io/badge/open--source-project-lightgray?style=for-the-badge">
	</a>
	<a href="https://github.com/floripasat/ttc">
		<img src="https://img.shields.io/badge/flight-heritage-lightgray?style=for-the-badge">
	</a>
</p>

<p align="center">
    <a href="#overview">Overview</a> •
    <a href="#license">License</a> •
    <a href="#releases">Releases</a> •
</p>

<p align="center">
    <img width="70%" src="https://github.com/spacelab-ufsc/ttc/blob/master/doc/figures/ttc_board.png">
</p>

## Overview

The TTC (or TT&C) is the communication module of the CubeSats from SpaceLab. It is responsible to make the communication between the earth (a ground station) and a satellite, and is divided in two sub-modules: Beacon and telemetry.

The beacon is a independent sub-module who transmits a periodic signal containing an identification data (ID) of the satellite and some basic telemetry data. The telemetry sub-module is the main communication device. It has a bidirectional data link to receive telecommands from the earth and transmit all the requested data. The telemetry sub-module is controlled by an external device (as example, an OBDH module).

## License

This project is open-source under three different licenses: GNU General Public License v3.0 for firmware sources, CERN Open Hardware License v2.0 for hardware files, and CC BY-SA 4.0 for the documentation. Some third-part files and libraries are subjected to their specific terms and licenses.

## Releases

The TTC software and hardware releases are synchronized in order to garantee compatibility. Then, using diferent versions might lead to unpredictable behavior. Refer to the [documentation](https://github.com/spacelab-ufsc/ttc/tree/master/doc) for compatibility notes.
