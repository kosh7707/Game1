set GAMESERVER_PATH=../Server/GameServer
set DUMMYCLIENT_PATH=../Server/DummyClient
set CLIENT_PATH=../Client/Assets/Scripts/Packet

protoc.exe -I=./ --cpp_out=./ --csharp_out=./ ./Enum.proto
protoc.exe -I=./ --cpp_out=./ --csharp_out=./ ./Struct.proto
protoc.exe -I=./ --cpp_out=./ --csharp_out=./ ./Protocol.proto

GenPackets.exe --path=./Protocol.proto --output=ClientPacketHandler --recv=C_ --send=S_ --process=cpp
GenPackets.exe --path=./Protocol.proto --output=ServerPacketHandler --recv=S_ --send=C_ --process=cpp
GenPackets.exe --path=./Protocol.proto --output=PacketManager --recv=S_ --send=C_ --process=cs

if ERRORLEVEL 1 (
    echo An error occurred during processing. Press any key to continue...
    pause
    exit /b 1
)

xcopy /Y Enum.pb.h "./GameServer"
xcopy /Y Enum.pb.cc "./GameServer"
xcopy /Y Struct.pb.h "./GameServer"
xcopy /Y Struct.pb.cc "./GameServer"
xcopy /Y Protocol.pb.h "./GameServer"
xcopy /Y Protocol.pb.cc "./GameServer"
xcopy /Y ClientPacketHandler.h "./GameServer"
xcopy /Y /S /I "./GameServer" "%GAMESERVER_PATH%"

xcopy /Y Enum.pb.h "./DummyClient"
xcopy /Y Enum.pb.cc "./DummyClient"
xcopy /Y Struct.pb.h "./DummyClient"
xcopy /Y Struct.pb.cc "./DummyClient"
xcopy /Y Protocol.pb.h "./DummyClient"
xcopy /Y Protocol.pb.cc "./DummyClient"
xcopy /Y ServerPacketHandler.h "./DummyClient"
xcopy /Y /S /I "./DummyClient" "%DUMMYCLIENT_PATH%"

xcopy /Y Enum.cs "./Client"
xcopy /Y Struct.cs "./Client"
xcopy /Y Protocol.cs "./Client"
xcopy /Y PacketManager.cs "./Client"
xcopy /Y /S /I "./Client" "%CLIENT_PATH%"

del /Q /F *.cs
del /Q /F *.cc
del /Q /F *.h