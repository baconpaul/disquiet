#!/bin/sh

cmake . -GXcode -Bbuild
xcodebuild build -configuration Release -project build/disquiet0433.xcodeproj -target run_drums

