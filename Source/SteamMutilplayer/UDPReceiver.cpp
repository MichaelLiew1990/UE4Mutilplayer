#include "SteamMutilplayer.h"
#include "UDPReceiver.h"

AUDPReceiver::AUDPReceiver(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ListenSocket = NULL;
}

void AUDPReceiver::BeginPlay()
{
	Super::BeginPlay();
	
	StartUDPReceiver("Receiver", 8890);
}

void AUDPReceiver::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	ScreenMsg("RECEIVER EndPlay");

	delete UDPReceiver;
	UDPReceiver = nullptr;

	//Clear all sockets!
	//		makes sure repeat plays in Editor dont hold on to old sockets!
	if (ListenSocket)
	{
		ListenSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ListenSocket);
	}
}

bool AUDPReceiver::StartUDPReceiver(
	const FString& YourChosenSocketName,
	const int32 ThePort,
	const FString& TheIP
	) {

	ScreenMsg("RECEIVER INIT");

	FIPv4Address Addr;
	FIPv4Address::Parse(TheIP, Addr);

	//Create Socket
	FIPv4Endpoint Endpoint(/*FIPv4Address::Any*/Addr, ThePort);

	int32 BufferSize = 2 * 1024 * 1024;

	ListenSocket = FUdpSocketBuilder(*YourChosenSocketName)
		.AsNonBlocking()
		.AsReusable()
		.BoundToEndpoint(Endpoint)
		.WithReceiveBufferSize(BufferSize);

	FTimespan ThreadWaitTime = FTimespan::FromSeconds(0.1);//FTimespan::FromMilliseconds(100);
	UDPReceiver = new FUdpSocketReceiver(ListenSocket, ThreadWaitTime, TEXT("UDP RECEIVER"));
	UDPReceiver->OnDataReceived().BindUObject(this, &AUDPReceiver::Recv);
	UDPReceiver->Start();

	return true;
}

void AUDPReceiver::Recv(const FArrayReaderPtr& ArrayReaderPtr, const FIPv4Endpoint& EndPt)
{
	FCustomSendData Data;
	*ArrayReaderPtr << Data;

	BPEvent_DataReceived(Data);//BP Event
}