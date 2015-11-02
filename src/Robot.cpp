#include "WPILib.h"
#include "DeadSwipe.h"
#include "UsefulMath.h"
#include "F310.h"

class Robot: public SampleRobot
{
	// class wide declarations

	// drive train declarations - anything prefixed with db is a part of the drive train

	// motor declarations - motors are controlled by motor controllers. We use Talons
	Talon *dbFrontLeft; // pwm 6
	Talon *dbRearLeft; // pwm 4
	Talon *dbFrontRight; // pwm 7
	Talon *dbRearRight; // pwm 9
	RobotDrive *dbDrive; // easy tools ftw
	Talon *dbMiddleLeft; // pwm 5
	Talon *dbMiddleRight; // pwm 8

	// encoder declarations - encoders require 2 digital I/O pins and are used to measured how far a rotating object
	// has moved
	Encoder *dbLeftEncoder; // DIO 0 and 1
	Encoder *dbRightEncoder; // DIO 2 and 3
	Encoder *dbMidEncoder; // DIO 4 and 5

	// gyro declaration - gyros allow us to measure how much an object has rotated along an axis
	// NOTE: gyros can(as of this writing) ONLY be used on AIN 0 and 1
	Gyro *dbGyro; // AIN 0

	// Elevator declarations

	Talon *eLeft; // pwm 0
	Talon *eRight; // pwm 1

	DoubleSolenoid *epLeft; // PCM ports 3 and 4
	DoubleSolenoid *epRight; // PCM ports 2 and 5

	DigitalInput *eLeftBottom; // DIO 6
	DigitalInput *eLeftTop; // DIO 7
	DigitalInput *eRightBottom; // DIO 8
	DigitalInput *eRightTop; // DIO 9

//	Encoder *eLeftEnc; // DIO 6 and 7
//	Encoder *eRightEnc; // DIO 8 and 9

	// intake declarations

	Talon *iLeft; // pwm 2
	Talon *iRight; // pwm 3

	DoubleSolenoid *ipLeft; // PCM ports 1 and 6
	DoubleSolenoid *ipRight; // PCM ports 0 and 7

	// operator interface declarations - prefixed by oi
	Joystick *oiLeft;
	Joystick *oiRight;
	Joystick *oiGamepad;
	SendableChooser *autoChooser; // this is how we'll select different
	int mode1 = 0;
	int mode2 = 1;
	Compressor *pCompressor;

public:

	Robot()
	{
		oiLeft = new Joystick(0);
		oiRight = new Joystick(1);
		oiGamepad = new Joystick(2);
		autoChooser = new SendableChooser();
		autoChooser->AddDefault("Do Nuffin", (int *) mode1);
		autoChooser->AddObject("Move you goddamm robot", (int *) mode2);

		dbFrontLeft = new Talon(6);
		dbRearLeft = new Talon(4);
		dbFrontRight = new Talon(7);
		dbRearRight = new Talon(9);

		dbDrive = new RobotDrive(dbFrontLeft, dbRearLeft, dbFrontRight,
				dbRearRight);
		dbDrive->SetSafetyEnabled(true);
		dbDrive->SetExpiration(0.1);
		dbDrive->SetSensitivity(0.5);
		dbDrive->SetMaxOutput(1.0);

		dbMiddleLeft = new Talon(5);
		dbMiddleRight = new Talon(8);

		dbLeftEncoder = new Encoder(0, 1, false, Encoder::k4X);
		dbLeftEncoder->SetDistancePerPulse(DRIVE_DISTANCE_PER_PULSE);

		dbRightEncoder = new Encoder(2, 3, false, Encoder::k4X);
		dbRightEncoder->SetDistancePerPulse(DRIVE_DISTANCE_PER_PULSE);

		dbMidEncoder = new Encoder(4, 5, false, Encoder::k4X);
		dbMidEncoder->SetDistancePerPulse(MIDDLE_DISTANCE_PER_PULSE);

		dbGyro = new Gyro(0);
		dbGyro->SetSensitivity(0.007);

		epLeft = new DoubleSolenoid(0, 3, 4);
		epRight = new DoubleSolenoid(0, 2, 5);

		eLeft = new Talon(2);
		eRight = new Talon(3);

//		eLeftEnc = new Encoder(6, 7, false, Encoder::k4X);
//		eLeftEnc->SetDistancePerPulse(OPTICAL_PPR);
//
//		eRightEnc = new Encoder(8, 9, true, Encoder::k4X);
//		eRightEnc->SetDistancePerPulse(OPTICAL_PPR);

		eLeftBottom = new DigitalInput(6);
		eLeftTop = new DigitalInput(7);
		eRightBottom = new DigitalInput(8);
		eRightTop = new DigitalInput(9);

		ipLeft = new DoubleSolenoid(0, 1, 6);
		ipRight = new DoubleSolenoid(0, 0, 7);

		iLeft = new Talon(0);
		iRight = new Talon(1);

		pCompressor = new Compressor();

	} // end of constructor

	void Autonomous(void)
	{
		int aSelectedMode = (int) autoChooser->GetSelected();
		while (IsEnabled() && IsAutonomous())
		{
			this->Debug();
			switch (aSelectedMode)
			{
			case 1:
				break;
			case 2:
				break;
			default:
				break;
			}
			this->Debug();

		} // end of while loop

	} // end of auton

	void OperatorControl(void)
	{
		bool manualOverride = true;

		while (IsOperatorControl() && IsEnabled())
		{
			this->Debug();

			if (oiLeft->GetRawButton(1) == true)
			{
				iRight->Set(-1.0);
				iLeft->Set(1.0);
			}
			iLeft->Set(0);
			iRight->Set(0);

			if (oiLeft->GetRawButton(3) == true)
			{
				iRight->Set(1.0);
				iLeft->Set(-1.0);
			}

			if (oiGamepad->GetRawButton(1) == true)
			{
				epLeft->Set(DoubleSolenoid::kForward);
				epRight->Set(DoubleSolenoid::kReverse);
			}

			if (oiGamepad->GetRawButton(3) == true)
			{
				epLeft->Set(DoubleSolenoid::kReverse);
				epRight->Set(DoubleSolenoid::kForward);
			}

			if (oiGamepad->GetRawButton(2) == true)
			{
				ipLeft->Set(DoubleSolenoid::kReverse);
				ipRight->Set(DoubleSolenoid::kReverse);
			}

			if (oiGamepad->GetRawButton(4) == true)
			{
				ipLeft->Set(DoubleSolenoid::kForward);
				ipRight->Set(DoubleSolenoid::kForward);
			}

			if (oiGamepad->GetRawButton(10) == true)
			{
				if (manualOverride == true)
				{
					manualOverride = false;
				}
				else if (manualOverride == false)
				{
					manualOverride = true;
				}
			}

			if (oiGamepad->GetRawButton(6) == true)
			{
				eLeft->Set(1.0);
				eRight->Set(1.0);
			}
			else if (!oiGamepad->GetRawButton(6) == true)
			{
				eLeft->Set(0.0);
				eRight->Set(0.0);
			}

			if (oiGamepad->GetRawButton(8) == true)
			{
				eLeft->Set(-1.0);
				eRight->Set(-1.0);
			}
			else if (!oiGamepad->GetRawButton(8) == true)
			{
				eLeft->Set(0.0);
				eRight->Set(0.0);
			}

			if (oiGamepad->GetRawButton(10) == true)
			{
				pCompressor->Stop();
			}
//			if(oiGamepad->GetButton(F310::kRightTrigger) == true)
//				{
//					 if((eLeftTop->Get() == 0) && (eRightTop->Get() == 0))
//					 {
//						 eLeft->Set(1.0);
//						 eRight->Set(1.0);							 }							else
//						 {
//							 eLeft->Set(0.0);
//							 eRight->Set(0.0);
//						 }
//					}
//
//						if(oiGamepad->GetButton(F310::kLeftTrigger) == true)
//						{
//							if((eLeftBottom->Get() == 0) && (eRightBottom->Get() == 0))
//							{
//								eLeft->Set(-1.0);
//								eRight->Set(-1.0);
//							}
//							else
//							{
//								eLeft->Set(0.0);
//								eRight->Set(0.0);
//							}
//						}

			HDrive(0.0);

//			float lyDrive = scaleyFunction(oiLeft->GetY(), 0, 3);
//			float ryDrive = scaleyFunction(oiRight->GetY(), 0, 3);
//			float xDrive = scaleyFunction(oiRight->GetX(), 0, 3);

//			dbDrive->TankDrive(lyDrive, ryDrive);
//			if (oiRight->GetButton(1) == true)
//			{
//				this->HDrive(xDrive);
//			}

			dbDrive->TankDrive(-oiLeft->GetY(), -oiRight->GetY());
			if (oiRight->GetRawButton(1) == true)
			{
				this->HDrive(oiRight->GetX());
			}
			if (manualOverride)
			{
				eLeft->Set(-oiGamepad->GetRawAxis(1));
				eRight->Set(-oiGamepad->GetRawAxis(3));
			}
			else if (!manualOverride)
			{
				iLeft->Set(-oiGamepad->GetRawAxis(1));
				iRight->Set(-oiGamepad->GetRawAxis(3));
			}

			SmartDashboard::PutBoolean("ManualOverride:",
					manualOverride);
			SmartDashboard::PutBoolean("Pressure Switch",
					pCompressor->GetPressureSwitchValue());
			SmartDashboard::PutNumber("iRIght", iRight->Get());
			SmartDashboard::PutNumber("iLEft", iLeft->Get());

		} // end or while loop

	} // end of teleop

	void Disabled(void)
	{

	}

	void Test(void)
	{

	}

	// h drive function
	void HDrive(float speed)
	{
		dbMiddleLeft->Set(speed);
		dbMiddleRight->Set(speed);
	}

	// elevator pneumatic function
	void ePneumaticControl(int x)
	{
		switch (x)
		{
		case L_OPEN:
			this->epLeft->Set(DoubleSolenoid::kReverse);
			break;
		case L_CLOSE:
			this->epLeft->Set(DoubleSolenoid::kForward);
			break;
		case R_OPEN:
			this->epRight->Set(DoubleSolenoid::kReverse);
			break;
		case R_CLOSE:
			this->epRight->Set(DoubleSolenoid::kForward);
			break;
		case B_OPEN:
			this->epLeft->Set(DoubleSolenoid::kReverse);
			this->epRight->Set(DoubleSolenoid::kReverse);
			break;
		case B_CLOSE:
			this->epLeft->Set(DoubleSolenoid::kForward);
			this->epRight->Set(DoubleSolenoid::kForward);
			break;
		default:
			break;
		}
	}

	// intake pnematic function
	void iPneumaticControl(int x)
	{
		switch (x)
		{
		case L_OPEN:
			this->ipLeft->Set(DoubleSolenoid::kReverse);
			break;
		case L_CLOSE:
			this->ipLeft->Set(DoubleSolenoid::kForward);
			break;
		case R_OPEN:
			this->ipRight->Set(DoubleSolenoid::kReverse);
			break;
		case R_CLOSE:
			this->ipRight->Set(DoubleSolenoid::kForward);
			break;
		case B_OPEN:
			this->ipLeft->Set(DoubleSolenoid::kReverse);
			this->ipRight->Set(DoubleSolenoid::kReverse);
			break;
		case B_CLOSE:
			this->ipLeft->Set(DoubleSolenoid::kForward);
			this->ipRight->Set(DoubleSolenoid::kForward);
			break;
		default:
			break;
		}
	}
	// drive train debug function
	void dbDebug()
	{
		SmartDashboard::PutNumber("dbMiddle:",
				dbMidEncoder->GetDistance());
		SmartDashboard::PutNumber("dbLeft:",
				dbLeftEncoder->GetDistance());
		SmartDashboard::PutNumber("dbRight:",
				dbRightEncoder->GetDistance());
		SmartDashboard::PutNumber("dbGyro:", dbGyro->GetAngle());
	}

	// elevator debug function
	void eDebug()
	{
//		SmartDashboard::PutNumber("eLeft", eLeftEnc->GetDistance());
//		SmartDashboard::PutNumber("eRight", eRightEnc->GetDistance());
//		SmartDashboard::PutNumber("eLeft Pulses", eLeftEnc->Get());
//		SmartDashboard::PutNumber("eLeft revs", eLeftEnc->Get() / OPTICAL_PPR);
//		float LRevs = eLeftEnc->Get() / OPTICAL_PPR;
//		SmartDashboard::PutNumber("eLeft Pulses per rev", EncoderMagic(LRevs));
//		SmartDashboard::PutNumber("eRight pulses", eRightEnc->Get());
//		SmartDashboard::PutNumber("eRight revs", eRightEnc->Get() / OPTICAL_PPR);
//		float RRevs = eRightEnc->Get() / OPTICAL_PPR;
//		SmartDashboard::PutNumber("eRight pulses per rev", EncoderMagic(RRevs));
	}

	void Debug()
	{
		this->dbDebug();
		this->eDebug();
	}
};
START_ROBOT_CLASS(Robot);
