pushd %~dp0

pyinstaller --clean -F -n GenPackets --distpath ./ PacketGenerator.py

