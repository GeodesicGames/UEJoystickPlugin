#pragma once

#include <IInputDevice.h>
#include "JoystickInterface.h"

class FDeviceSDL;

class IJoystickEventInterface
{
public:
	virtual ~IJoystickEventInterface()
	{
	}

	virtual void JoystickPluggedIn(FDeviceIndex DeviceIndex) = 0;
	virtual void JoystickUnplugged(FDeviceId DeviceId) = 0;
	virtual void JoystickButton(FDeviceId DeviceId, int32 Button, bool Pressed) = 0;
	virtual void JoystickAxis(FDeviceId DeviceId, int32 Axis, float Value) = 0;
	virtual void JoystickHat(FDeviceId DeviceId, int32 Hat, EJoystickPOVDirection Value) = 0;
	virtual void JoystickBall(FDeviceId DeviceId, int32 Ball, int DeltaX, int DeltaY) = 0;
};

class FJoystickDevice : public IInputDevice, public IJoystickEventInterface
{
public:
	FJoystickDevice();
	~FJoystickDevice();

	void Tick(float DeltaTime) override;
	void SendControllerEvents() override;
	void SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override;
	bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;
	void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override;
	void SetChannelValues(int32 ControllerId, const FForceFeedbackValues& Values) override;

	bool AddEventListener(UObject* Listener);

	virtual void JoystickPluggedIn(FDeviceIndex DeviceIndex) override;
	virtual void JoystickUnplugged(FDeviceId DeviceId) override;
	virtual void JoystickButton(FDeviceId DeviceId, int32 Button, bool Pressed) override;
	virtual void JoystickAxis(FDeviceId DeviceId, int32 Axis, float Value) override;
	virtual void JoystickHat(FDeviceId DeviceId, int32 Hat, EJoystickPOVDirection Value) override;
	virtual void JoystickBall(FDeviceId DeviceId, int32 Ball, int DeltaX, int DeltaY) override;

	TMap<FDeviceId, FJoystickState> CurrentState;
	TMap<FDeviceId, FJoystickState> PreviousState;

	TMap<FDeviceId, FJoystickInfo> InputDevices;
private:
	bool AddInputDevice(FDeviceId DeviceId);

	FDeviceSDL *DeviceSDL = nullptr;
	TArray<TWeakObjectPtr<UObject>> EventListeners;

	TMap<FDeviceId, TArray<FKey>> DeviceButtonKeys;
	TMap<FDeviceId, TArray<FKey>> DeviceAxisKeys;
	TMap<FDeviceId, TArray<FKey>> DeviceHatKeys[2];
	//TMap<DeviceId, TArray<FKey>> DeviceBallKeys[2];
};