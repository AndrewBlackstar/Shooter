// Fill out your copyright notice in the Description page of Project Settings.


#include "S_Character01.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapons/S_Weapon.h"

// Sets default values
AS_Character01::AS_Character01()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseFirstPersonView = true;
	FpsCameraSocket = TEXT("SCK_Camera");

	SprintSpeed = 2100;
	RunSpeed = 600;

	// Create a camera component
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCamera"));
	FPSCameraComponent->bUsePawnControlRotation = true; // Rotate the camera based on the controller
	FPSCameraComponent->SetupAttachment(GetMesh(), FpsCameraSocket);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraBoom->SetupAttachment(RootComponent);

	// Create a camera component
	TPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TPSCamera"));
	TPSCameraComponent->SetupAttachment(CameraBoom);

	// 👇 HABILITAR AGACHARSE
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

}

FVector AS_Character01::GetPawnViewLocation() const
{
	if (IsValid(FPSCameraComponent) && bUseFirstPersonView)
	{
		return FPSCameraComponent->GetComponentLocation();
	}
	else if (IsValid(TPSCameraComponent) && !bUseFirstPersonView)
	{
		return TPSCameraComponent->GetComponentLocation();
	}

	return Super::GetPawnViewLocation();
}


// Called when the game starts or when spawned
void AS_Character01::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	BaseWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	SwitchCamera();
	CreateInitialWeapon();
}

void AS_Character01::SwitchCamera()
{
	bUseFirstPersonView = !bUseFirstPersonView;

	if (bUseFirstPersonView)
	{
		TPSCameraComponent->Deactivate();
		FPSCameraComponent->Activate();
	}
	else
	{
		FPSCameraComponent->Deactivate();
		TPSCameraComponent->Activate();
	}

	// Aplicar la cámara al PlayerController
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		UCameraComponent* ActiveCamera = bUseFirstPersonView ? FPSCameraComponent : TPSCameraComponent;
		PC->SetViewTargetWithBlend(this, 0.25f); // Usa el blend para transición suave
	}

	
	
}



// Called every frame
void AS_Character01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AS_Character01::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
	
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AS_Character01::Move);

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AS_Character01::Look);

		//Switching Camera
		EnhancedInputComponent->BindAction(SwitchCameraAction, ETriggerEvent::Started, this, &AS_Character01::SwitchCamera);

		//Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AS_Character01::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AS_Character01::StopSprint);
		//Crouching
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AS_Character01::StartCrouch);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AS_Character01::StopCrouch);

		//Firing
		EnhancedInputComponent->BindAction(WeaponAction, ETriggerEvent::Started, this, &AS_Character01::StartWeaponAction);
		EnhancedInputComponent->BindAction(WeaponAction, ETriggerEvent::Completed, this, &AS_Character01::StopWeaponAction);
	}
}


void AS_Character01::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AS_Character01::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisValue = Value.Get<FVector2D>();

	if (Controller != nullptr) {
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(bIsLookInversion ? -LookAxisValue.Y:LookAxisValue.Y);
	}
}

void AS_Character01::Jump()
{
	Super::Jump();
}

void AS_Character01::StopJumping()
{
	Super::StopJumping();
}

void AS_Character01::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AS_Character01::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	
}

void AS_Character01::StartCrouch()
{
	UE_LOG(LogTemp, Warning, TEXT("Crouch pressed"));
	Crouch();
}

void AS_Character01::StopCrouch()
{
	UnCrouch();
}

void AS_Character01::CreateInitialWeapon()
{
	if (IsValid(InitialWeaponClass))
	{
		CurrentWeapon = GetWorld()->SpawnActor<AS_Weapon>(InitialWeaponClass, GetActorLocation(), GetActorRotation());
		if (IsValid(CurrentWeapon))
		{
			CurrentWeapon->SetOwner(this);
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			CurrentWeapon->StartAction();
		}
	}
	
}

void AS_Character01::StartWeaponAction()
{
	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StartAction();
	}
	
}

void AS_Character01::StopWeaponAction()
{
	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StopAction();
	}
	
}

void AS_Character01::AddKey(FName NewKeyName)
{
	DoorKeys.Add(NewKeyName);
}

bool AS_Character01::HasKey(FName KeyName)
{
	return DoorKeys.Contains(KeyName);
}







