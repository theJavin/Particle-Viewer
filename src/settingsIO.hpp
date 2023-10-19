/*
 * settingsIO.hpp
 *
 * Loads position data from a binary file.
 *
 */

#ifndef SETTINGSIO_H
#define SETTINGSIO_H
#include <iostream>
#include <fstream>
#include <sstream>
#include "glm/glm.hpp"
#include "glad/glad.h"
#include "particle.hpp"
#include "tinyFileDialogs/tinyfiledialogs.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "../../Source/commonStructs.h"

class SettingsIO
{
public:
	std::string posName;
	std::string statsName;
	std::string comName;
	bool isPlaying;
	int errorCount;
	long N;
	long frames;

	/*
	 * Default constructor for SettingsIO, used for the default cube
	 */
	SettingsIO()
	{
		posFile = "/PosAndVel";
		statsFile = "/RunSetup";
		comFile = "/COMFile";
	}

	/*
	 * Loads a specific position file.
	 */
	SettingsIO(std::string posName, std::string statsName, std::string comName)
	{
		this->posName = posName;
		this->statsName = statsName;
		this->comName = comName;
		//std::ifstream data;
		posFile = "../../NodeStruct";
		statsFile = "/RunSetup";
		comFile = "/COMFile";
		//std::string name;
		std::string blank;
		errorCount = 0;
		isPlaying = false;
		//data.open(statsName.c_str());

		std::ifstream data;
		std::string name;
		
		data.open("../../simulationSetup");
		
		if(data.is_open() == 1)
		{
			getline(data,name,'=');
			//data >> NodesMusclesFileOrPreviousRunsFile;
			
			getline(data,name,'=');
			//data >> NodesMusclesFileName;
			
			getline(data,name,'=');
			//data >> PreviousRunFileName;
			
			getline(data,name,'=');
			data >> LineWidth;
			
			getline(data,name,'=');
			//data >> NodeRadiusAdjustment;
			
			getline(data,name,'=');
			//data >> MyocyteForcePerMass;
			
			getline(data,name,'=');
			//data >> MyocyteForcePerMassStDev;
			
			getline(data,name,'=');
			//data >> BloodPressure;
			
			getline(data,name,'=');
			//data >> MassOfAtria;
			
			getline(data,name,'=');
			//data >> RadiusOfAtria;
			
			getline(data,name,'=');
			//data >> BaseMuscleRelaxedStrength;
			
			getline(data,name,'=');
			//data >> BaseMuscleCompresionStopFraction;
			
			getline(data,name,'=');
			//data >> BaseMuscleCompresionStopFractionStDev;
			
			getline(data,name,'=');
			//data >> BaseMuscleContractionDuration;
			
			getline(data,name,'=');
			//data >> BaseMuscleContractionDurationStDev;
			
			getline(data,name,'=');
			//data >> BaseMuscleRechargeDuration;
			
			getline(data,name,'=');
			//data >> BaseMuscleRechargeDurationStDev;
			
			getline(data,name,'=');
			//data >> BaseMuscleConductionVelocity;
			
			getline(data,name,'=');
			//data >> BaseMuscleConductionVelocityStDev;
			
			getline(data,name,'=');
			//data >> MaxNumberOfperiodicEctopicEvents;
			
			getline(data,name,'=');
			//data >> BeatPeriod;
			
			getline(data,name,'=');
			//data >> PrintRate;
			
			getline(data,name,'=');
			data >> DrawRate;
			
			getline(data,name,'=');
			data >> Dt;
			
			getline(data,name,'=');
			//data >> ReadyColor.x;
			
			getline(data,name,'=');
			//data >> ReadyColor.y;
			
			getline(data,name,'=');
			//data >> ReadyColor.z;
			
			getline(data,name,'=');
			//data >> ContractingColor.x;
			
			getline(data,name,'=');
			//data >> ContractingColor.y;
			
			getline(data,name,'=');
			//data >> ContractingColor.z;
			
			getline(data,name,'=');
			//data >> RestingColor.x;
			
			getline(data,name,'=');
			//data >> RestingColor.y;
			
			getline(data,name,'=');
			//data >> RestingColor.z;
			
			getline(data,name,'=');
			//data >> DeadColor.x;
			
			getline(data,name,'=');
			//data >> DeadColor.y;
			
			getline(data,name,'=');
			//data >> DeadColor.z;
			
			getline(data,name,'=');
			//data >> BackGroundRed;
			
			getline(data,name,'=');
			//data >> BackGroundGreen;
			
			getline(data,name,'=');
			//data >> BackGroundBlue;
		}
		else
		{
			printf("\nTSU Error could not open simulationSetup file\n");
			exit(0);
		}
		/*
		else
		{
			this->InitialPosition1.x = 100;
			this->InitialPosition1.y = 100;
			this->InitialPosition1.z = 100;
			this->InitialPosition2.x = 100;
			this->InitialPosition2.y = 100;
			this->InitialPosition2.z = 100;
			this->InitialVelocity1.x = 100;
			this->InitialVelocity1.y = 100;
			this->InitialVelocity1.z = 100;
			this->InitialVelocity2.x = 100;
			this->InitialVelocity2.y = 100;
			this->InitialVelocity2.z = 100;
			this->InitialSpin1.x = 100;
			this->InitialSpin1.y = 100;
			this->InitialSpin1.z = 100;
			this->InitialSpin1.w = 100;
			this->InitialSpin2.x = 100;
			this->InitialSpin2.y = 100;
			this->InitialSpin2.z = 100;
			this->InitialSpin2.w = 100;
			this->FractionEarthMassOfBody1 = 100;
			this->FractionEarthMassOfBody2 = 100;
			this->FractionFeBody1 = 100;
			this->FractionSiBody1 = 100;
			this->FractionFeBody2 = 100;
			this->FractionSiBody2 = 100;
			this->DampRateBody1 = 100;
			this->DampRateBody2 = 100;
			this->EnergyTargetBody1 = 100;
			this->EnergyTargetBody2 = 100;
			this->N = 100;
			this->TotalRunTime = 100;
			this->DampTime = 100;
			this->DampRestTime = 100;
			this->EnergyAdjustmentTime = 100;
			this->EnergyAdjustmentRestTime = 100;
			this->SpinRestTime = 100;
			this->Dt = 100;
			this->WriteToFile = 100;
			this->RecordRate = 100;
			this->DensityFe = 100;
			this->DensitySi = 100;
			this->KFe = 100;
			this->KSi = 100;
			this->KRFe = 100;
			this->KRSi = 100;
			this->SDFe = 100;
			this->SDSi = 100;
			this->DrawRate = 100;
			this->DrawQuality = 100;
			this->UseMultipleGPU = 100;
			this->UniversalGravity = 100;
			this->MassOfEarth = 100;
			this->Pi = 100;
		}*/
		data.close();
		frames = getFrames();
	}

	~SettingsIO();

	/*
	 * Reads positions and velocities from a file at a specifc frame
	 */
	void readNodeStructFile(long frame, Particle *part,bool readVelocity)
	{
		FILE *NodeStructFile = fopen(posName.c_str(), "r");
		if(NodeStructFile)
		{
			if(frame >= frames)
			{
				frame = frames-1;
				isPlaying = false;
			}
			if(frame < 0)
			{
				frame = 0;
				isPlaying = false;
			}
			fseek(NodeStructFile, frame * sizeof(nodeAtributesStructure) * 2 * N, SEEK_CUR);
			glm::vec4 *pos = new glm::vec4[N];
			glm::vec4 *vel;
			fread(pos, sizeof(glm::vec4), (int)N, NodeStructFile);
			part->changeTranslations(N,pos);
			if(readVelocity)
			{
				vel = new glm::vec4[N];
				fread(vel, sizeof(glm::vec4), N, NodeStructFile);
				part->changeVelocities(vel);
				delete[] vel;
			}
			delete[] pos;
			fclose(NodeStructFile);
			return;
		}
		//fclose(NodeStructFile);
		errorCount++;
		if(errorCount < 5)
		{
			std::cout << "Error Reading File. Attempt: " << errorCount << std::endl;
		}
		else if (errorCount == 5)
		{
			std::cout << "Too many errors. stopping log here" << std::endl;
		}
	}

	/*
	 * Toggles playback.
	 */
	void togglePlay()
	{
		isPlaying = !isPlaying;
	}

	glm::vec3 getInitialPosition1()		{return InitialPosition1;}
	glm::vec3 getInitialPosition2()		{return InitialPosition2;}
	glm::vec3 getInitialVelocity1()		{return InitialVelocity1;}
	glm::vec3 getInitialVelocity2()		{return InitialVelocity2;}
	glm::vec4 getInitialSpin1()			{return InitialSpin1;}
	glm::vec4 getInitialSpin2()			{return InitialSpin2;}
	double getFractionEarthMassOfBody1(){return FractionEarthMassOfBody1;}
	double getFractionEarthMassOfBody2(){return FractionEarthMassOfBody2;}
	double getFractionFeBody1()			{return FractionFeBody1;}
	double getFractionSiBody1()			{return FractionSiBody1;}
	double getFractionFeBody2()			{return FractionFeBody2;}
	double getFractionSiBody2()			{return FractionSiBody2;}
	float getDampRateBody1()			{return DampRateBody1;}
	float getDampRateBody2()			{return DampRateBody2;}
	float getEnergyTargetBody1()		{return EnergyTargetBody1;}
	float getEnergyTargetBody2()		{return EnergyTargetBody2;}
	float getTotalRunTime()				{return TotalRunTime;}
	float getDampTime()					{return DampTime;}
	float getDampRestTime()				{return DampRestTime;}
	float getEnergyAdjustmentTime()		{return EnergyAdjustmentTime;}
	float getEnergyAdjustmentRestTime()	{return EnergyAdjustmentRestTime;}
	float getSpinRestTime()				{return SpinRestTime;}
	float getDt()						{return Dt;}
	int getWriteToFile()				{return WriteToFile;}
	int getRecordRate()					{return RecordRate;}
	double getDensityFe()				{return DensityFe;}
	double getDensitySi()				{return DensitySi;}
	double getKFe()						{return KFe;}
	double getKSi()						{return KSi;}
	double getKRFe()					{return KRFe;}
	double getKRSi()					{return KRSi;}
	double getSDFe()					{return SDFe;}
	double getSDSi()					{return SDSi;}
	int getDrawRate()					{return DrawRate;}
	int getDrawQuality()				{return DrawQuality;}
	int getUseMultipleGPU() 			{return UseMultipleGPU;}
	double getUniversalGravity()		{return UniversalGravity;}
	double getMassOfEarth()				{return MassOfEarth;}
	double getPi()						{return Pi;}

	/*
	 * Opens up a file dialog and loads particle data.
	 */
	SettingsIO* loadFile(Particle *part, bool readVelocity)
	{
		std::string dialog = "Select Folder";
		const char* fol = tinyfd_selectFolderDialog (dialog.c_str() , "") ;

		std::string folder;
		if(fol != NULL)
		{
			folder = std::string(fol);
		}
		else
		{
			folder = "";
		}
		if(folder != "")
		{
			std::string posVel = folder;//strcat(folder,posFile.c_str());
			posVel = posVel + posFile;
			std::string settings = folder + statsFile;//strcat(folder, settingsFile.c_str());
			std::string comName = folder + comFile;
			SettingsIO *set = new SettingsIO(posVel.c_str(),settings.c_str(),comName.c_str());
			set->readNodeStructFile(0,part,readVelocity);
			return set;
		}
		std::cout << "Folder not selected" << std::endl;
		return this;
	}

	/*
	 * Gets the total number of frames in a file.
	 */
	long long int getFrames()
	{
		std::ifstream input;
		input.open(posName, std::ios::in | std::ios::binary);
		if(input)
		{
			unsigned long long int size = 0;
			input.seekg(0,std::ios::end);
			size = input.tellg();
			size = size / (sizeof(glm::vec4) * 2 * N);
			input.seekg(0,std::ios::beg);
			return size;
		}
		std::cout << "Error Getting File Size" << std::endl;
		return 1;
	}

	/*
	 * Checks to see if a COMFile exists.
	 */
	bool checkCOM()
	{
		std::ifstream input;
		input.open(comName, std::ios::in | std::ios::binary);
		if(input)
		{
			input.close();
			return true;
		}
		//cout << "Error Loading Center Of Mass File" << endl;
		return false;
	}

	/*
	 * Grabs the center of mass from the COMFile.
	 */
	void getCOM(long frame, glm::vec3 &value)
	{
		if(checkCOM())
		{
			FILE *COMFile = fopen(comName.c_str(), "r");
			if(COMFile)
			{
				fseek(COMFile, frame * sizeof(glm::vec4), SEEK_CUR);
				glm::vec4 *readVal = new glm::vec4[1];
				fread(readVal, sizeof(glm::vec4), 1, COMFile);
				fclose(COMFile);
				if((long)readVal[0].w == frame)
				{
					value.x = readVal[0].x *.25;
					value.y = readVal[0].y *.25;
					value.z = readVal[0].z *.25;
				}

				return;
			}
		}
	}

private:
	//Note: most of these aren't used, but kept for posterity's sake and/or if the actual slam programs want to use this to simplify reading in stuff
	int RecordRate;
	int DrawRate;
	int DrawQuality;
	int WriteToFile;
	int UseMultipleGPU;
	float DampRateBody1;
	float DampRateBody2;
	float EnergyTargetBody1;
	float EnergyTargetBody2;
	float TotalRunTime;
	float DampTime;
	float DampRestTime;
	float EnergyAdjustmentTime;
	float EnergyAdjustmentRestTime;
	float SpinRestTime;
	float SetupTime;
	float Dt;
	double FractionEarthMassOfBody1;
	double FractionEarthMassOfBody2;
	double FractionFeBody1;
	double FractionSiBody1;
	double FractionFeBody2;
	double FractionSiBody2;
	double DensityFe;
	double DensitySi;
	double KFe;
	double KSi;
	double KRFe;
	double KRSi;
	double SDFe;
	double SDSi;
	double UniversalGravity;
	double MassOfEarth;
	double Pi;
	glm::vec3 InitialPosition1;
	glm::vec3 InitialPosition2;
	glm::vec3 InitialVelocity1;
	glm::vec3 InitialVelocity2;
	glm::vec4 InitialSpin1;
	glm::vec4 InitialSpin2;
	glm::vec4 CenterOfMass;
	std::string posFile;
	std::string statsFile;
	std::string comFile;
};

#endif /* SETTINGSIO_H */
