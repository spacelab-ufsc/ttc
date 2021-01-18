<h1 align="center">
    TTC DOCUMENTATION
    <br>
</h1>

<h4 align="center">Documentation of the TTC Module.</h4>

<p align="center">
    <a href="https://github.com/spacelab-ufsc/spacelab#versioning">
        <img src="https://img.shields.io/badge/status-in--orbit%20validated-blue?style=for-the-badge">
    </a>
    <a href="https://github.com/spacelab-ufsc/ttc/releases">
        <img alt="GitHub release (latest by date)" src="https://img.shields.io/github/v/release/spacelab-ufsc/ttc?style=for-the-badge">
    </a>
    <a href="https://github.com/spacelab-ufsc/ttc/releases">
        <img alt="GitHub commits since latest release (by date) for a branch" src="https://img.shields.io/github/commits-since/spacelab-ufsc/ttc/latest/documentation?style=for-the-badge">
    </a>
    <a href="https://github.com/spacelab-ufsc/ttc/commits/master">
        <img alt="GitHub last commit (branch)" src="https://img.shields.io/github/last-commit/spacelab-ufsc/ttc/documentation?style=for-the-badge">
    </a>
    <a href="https://github.com/spacelab-ufsc/ttc/issues">
    	<img alt="GitHub issues by-label" src="https://img.shields.io/github/issues/spacelab-ufsc/ttc/documentation?style=for-the-badge">
    </a>
    <a href="https://github.com/spacelab-ufsc/ttc/blob/master/firmware/main.c">
        <img src="https://img.shields.io/badge/language-C-green?style=for-the-badge">
    </a>
    <a href="#license">
        <img src="https://img.shields.io/badge/license-GPL3-yellow?style=for-the-badge">
    </a>
    <a href="https://github.com/spacelab-ufsc/ttc">
        <img src="https://img.shields.io/badge/flight-heritage-lightgray?style=for-the-badge">
    </a>
</p>

<p align="center">
	<a href="#overview">Overview</a> •
    <a href="#dependencies">Dependencies</a> •
    <a href="#version">Version</a> •
    <a href="#license">License</a>
</p>

## Overview

The TTC (or TT&C) is the communication module of the CubeSats from SpaceLab. It is responsible to make the communication between the earth (a ground station) and a satellite, and is divided in two sub-modules: Beacon and telemetry.

The beacon is a independent sub-module who transmits a periodic signal containing an identification data (ID) of the satellite and some basic telemetry data. This firmware implements the beacon sub-module.

## Dependencies

- MSP430 DriverLib v2.91.11.01
- NGHam protocol

## Version

Refer to the [releases](https://github.com/spacelab-ufsc/ttc/releases) page and the [version](https://github.com/spacelab-ufsc/ttc/blob/master/firmware/version.h) file.

## License

This repository containing firmware files is licensed under GPLv3 license.
