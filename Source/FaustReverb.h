//----------------------------------------------------------
//
// Code generated with Faust 0.9.92 (http://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>
#ifndef FAUSTPOWER
#define FAUSTPOWER
#include <cmath>
template <int N> inline int faustpower(int x)              { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline int faustpower<0>(int x)            { return 1; }
template <> 	 inline int faustpower<1>(int x)            { return x; }
template <> 	 inline int faustpower<2>(int x)            { return x*x; }
template <int N> inline float faustpower(float x)            { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline float faustpower<0>(float x)          { return 1; }
template <> 	 inline float faustpower<1>(float x)          { return x; }
template <> 	 inline float faustpower<2>(float x)          { return x*x; }
#endif
// Music 256a / CS 476a | fall 2016
// CCRMA, Stanford University
//
// Author: Romain Michon (rmichonATccrmaDOTstanfordDOTedu)
// Description: Simple Faust architecture file to easily integrate a Faust DSP module
// in a JUCE project

// needed by any Faust arch file
/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/
 
#ifndef __misc__
#define __misc__

#include <algorithm>
#include <map>
#include <string.h>
#include <stdlib.h>

/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 3 of
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program; If not, see <http://www.gnu.org/licenses/>.

 ************************************************************************
 ************************************************************************/
 
#ifndef __meta__
#define __meta__

struct Meta
{
    virtual void declare(const char* key, const char* value) = 0;
    virtual ~Meta() {};
};

#endif

using std::max;
using std::min;

struct XXXX_Meta : std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

struct MY_Meta : Meta, std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key]=value; }
};

inline int lsr(int x, int n)	{ return int(((unsigned int)x) >> n); }

inline int int2pow2(int x)		{ int r = 0; while ((1<<r) < x) r++; return r; }

inline long lopt(char* argv[], const char* name, long def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return atoi(argv[i+1]);
	return def;
}

inline bool isopt(char* argv[], const char* name)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return true;
	return false;
}

inline const char* lopts(char* argv[], const char* name, const char* def)
{
	int	i;
	for (i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return argv[i+1];
	return def;
}

#endif


// allows to control a Faust DSP module in a simple manner by using parameter's path
/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/

#ifndef FAUST_MAPUI_H
#define FAUST_MAPUI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <vector>
#include <map>
#include <string>

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2016 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/
 
#ifndef FAUST_UI_H
#define FAUST_UI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust User Interface
 * This abstract class contains only the method that the faust compiler can
 * generate to describe a DSP interface.
 ******************************************************************************/

class UI
{

    public:

        UI() {}

        virtual ~UI() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) = 0;
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) = 0;

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT*, const char*, const char*) {}
};

//----------------------------------------------------------------
//  Generic decorator
//----------------------------------------------------------------

class DecoratorUI : public UI
{
    protected:
    
        UI* fUI;

    public:
    
        DecoratorUI(UI* ui = 0):fUI(ui)
        {}

        virtual ~DecoratorUI() { delete fUI; }

        // -- widget's layouts
        virtual void openTabBox(const char* label)          { fUI->openTabBox(label); }
        virtual void openHorizontalBox(const char* label)   { fUI->openHorizontalBox(label); }
        virtual void openVerticalBox(const char* label)     { fUI->openVerticalBox(label); }
        virtual void closeBox()                             { fUI->closeBox(); }

        // -- active widgets
        virtual void addButton(const char* label, FAUSTFLOAT* zone)         { fUI->addButton(label, zone); }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)    { fUI->addCheckButton(label, zone); }
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
            { fUI->addVerticalSlider(label, zone, init, min, max, step); }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 	
            { fUI->addHorizontalSlider(label, zone, init, min, max, step); }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) 			
            { fUI->addNumEntry(label, zone, init, min, max, step); }

        // -- passive widgets	
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
            { fUI->addHorizontalBargraph(label, zone, min, max); }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
            { fUI->addVerticalBargraph(label, zone, min, max); }

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val) { fUI->declare(zone, key, val); }

};

#endif
/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.


 ************************************************************************
 ************************************************************************/

#ifndef FAUST_PATHBUILDER_H
#define FAUST_PATHBUILDER_H

#include <vector>
#include <string>
#include <algorithm>

/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class PathBuilder
{

    protected:
    
        std::vector<std::string> fControlsLevel;
       
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            replace(res.begin(), res.end(), ' ', '_');
            return res;
        }
    
};

#endif  // FAUST_PATHBUILDER_H

/*******************************************************************************
 * MapUI : Faust User Interface
 * This class creates a map of complete hierarchical path and zones for each UI items.
 ******************************************************************************/

class MapUI : public UI, public PathBuilder
{
    
    protected:
    
        // Complete path map
        std::map<std::string, FAUSTFLOAT*> fPathZoneMap;
    
        // Label zone map
        std::map<std::string, FAUSTFLOAT*> fLabelZoneMap;
    
    public:
        
        MapUI() {};
        virtual ~MapUI() {};
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openHorizontalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void openVerticalBox(const char* label)
        {
            fControlsLevel.push_back(label);
        }
        void closeBox()
        {
            fControlsLevel.pop_back();
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- metadata declarations
        void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
        
        // set/get
        void setParamValue(const std::string& path, float value)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                *fPathZoneMap[path] = value;
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                *fLabelZoneMap[path] = value;
            }
        }
        
        float getParamValue(const std::string& path)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                return *fPathZoneMap[path];
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                return *fLabelZoneMap[path];
            } else {
                return 0.;
            }
        }
    
        // map access 
        std::map<std::string, FAUSTFLOAT*>& getMap() { return fPathZoneMap; }
        
        int getParamsCount() { return fPathZoneMap.size(); }
        
        std::string getParamAdress(int index) 
        { 
            std::map<std::string, FAUSTFLOAT*>::iterator it = fPathZoneMap.begin();
            while (index-- > 0 && it++ != fPathZoneMap.end()) {}
            return (*it).first;
        }
};

#endif // FAUST_MAPUI_H

// needed by any Faust arch file
/************************************************************************
    IMPORTANT NOTE : this file contains two clearly delimited sections :
    the ARCHITECTURE section (in two parts) and the USER section. Each section
    is governed by its own copyright and license. Please check individually
    each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 3 of
    the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; If not, see <http://www.gnu.org/licenses/>.

    EXCEPTION : As a special exception, you may create a larger work
    that contains this FAUST architecture section and distribute
    that work under terms of your choice, so long as this FAUST
    architecture section is not modified.

 ************************************************************************
 ************************************************************************/
 
/******************************************************************************
*******************************************************************************

								FAUST DSP

*******************************************************************************
*******************************************************************************/

#ifndef __dsp__
#define __dsp__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

class UI;
struct Meta;

/**
* Signal processor definition.
*/

class dsp {

    public:

        dsp() {}
        virtual ~dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the UI* parameter with instance specific calls
         * to 'addBtton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the UI* user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Returns the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /** Global init, calls the following methods :
         * - static class 'classInit' : static table initialisation
         * - 'instanceInit' : constants and instance table initialisation
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void init(int samplingRate) = 0;
    
        /** Init instance state
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void instanceInit(int samplingRate) = 0;
    
        /** Init instance constant state
         *
         * @param samplingRate - the sampling rate in Herz
         */
        virtual void instanceConstants(int samplingRate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (delay lines...) */
        virtual void instanceClear() = 0;
    
        /**  
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value metadata).
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with sucessive in/out audio buffers.
         *
         * @param count - the nomber of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation : alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the nomber of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, doucbe or quad)
         *
         */
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = 0):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int samplingRate) { fDSP->init(samplingRate); }
        virtual void instanceInit(int samplingRate) { fDSP->instanceInit(samplingRate); }
        virtual void instanceConstants(int samplingRate) { fDSP->instanceConstants(samplingRate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { return fDSP->metadata(m); }
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
       
};

/**
 * On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
 * flags to avoid costly denormals.
 */

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif

// tags used by the Faust compiler to paste the generated c++ code
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  


#ifndef FAUSTCLASS 
#define FAUSTCLASS reverb
#endif

class reverb : public dsp {
  private:
	FAUSTFLOAT 	fslider0;
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider1;
	float 	fConst2;
	FAUSTFLOAT 	fslider2;
	float 	fConst3;
	float 	fConst4;
	FAUSTFLOAT 	fslider3;
	FAUSTFLOAT 	fslider4;
	float 	fConst5;
	FAUSTFLOAT 	fslider5;
	float 	fRec12[2];
	float 	fRec11[2];
	int 	IOTA;
	float 	fVec0[8192];
	float 	fConst6;
	int 	iConst7;
	float 	fVec1[8192];
	float 	fConst8;
	FAUSTFLOAT 	fslider6;
	float 	fVec2[1024];
	int 	iConst9;
	float 	fRec9[2];
	float 	fConst10;
	float 	fConst11;
	float 	fRec16[2];
	float 	fRec15[2];
	float 	fVec3[8192];
	float 	fConst12;
	int 	iConst13;
	float 	fVec4[2048];
	int 	iConst14;
	float 	fRec13[2];
	float 	fConst15;
	float 	fConst16;
	float 	fRec20[2];
	float 	fRec19[2];
	float 	fVec5[8192];
	float 	fConst17;
	int 	iConst18;
	float 	fVec6[2048];
	int 	iConst19;
	float 	fRec17[2];
	float 	fConst20;
	float 	fConst21;
	float 	fRec24[2];
	float 	fRec23[2];
	float 	fVec7[8192];
	float 	fConst22;
	int 	iConst23;
	float 	fVec8[1024];
	int 	iConst24;
	float 	fRec21[2];
	float 	fConst25;
	float 	fConst26;
	float 	fRec28[2];
	float 	fRec27[2];
	float 	fVec9[16384];
	float 	fConst27;
	int 	iConst28;
	float 	fVec10[2048];
	int 	iConst29;
	float 	fRec25[2];
	float 	fConst30;
	float 	fConst31;
	float 	fRec32[2];
	float 	fRec31[2];
	float 	fVec11[8192];
	float 	fConst32;
	int 	iConst33;
	float 	fVec12[2048];
	int 	iConst34;
	float 	fRec29[2];
	float 	fConst35;
	float 	fConst36;
	float 	fRec36[2];
	float 	fRec35[2];
	float 	fVec13[16384];
	float 	fConst37;
	int 	iConst38;
	float 	fVec14[2048];
	int 	iConst39;
	float 	fRec33[2];
	float 	fConst40;
	float 	fConst41;
	float 	fRec40[2];
	float 	fRec39[2];
	float 	fVec15[16384];
	float 	fConst42;
	int 	iConst43;
	float 	fVec16[1024];
	int 	iConst44;
	float 	fRec37[2];
	float 	fRec1[3];
	float 	fRec2[3];
	float 	fRec3[3];
	float 	fRec4[3];
	float 	fRec5[3];
	float 	fRec6[3];
	float 	fRec7[3];
	float 	fRec8[3];
	float 	fRec0[3];
	FAUSTFLOAT 	fslider7;
	FAUSTFLOAT 	fslider8;
	float 	fRec41[3];
	FAUSTFLOAT 	fslider9;
	float 	fRec42[2];
	FAUSTFLOAT 	fslider10;
	float 	fRec43[2];
	float 	fRec44[3];
	float 	fRec45[3];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/version", "2.0");
		m->declare("reverb.lib/name", "Faust Reverb Library");
		m->declare("reverb.lib/version", "0.0");
		m->declare("math.lib/name", "Faust Math Library");
		m->declare("math.lib/version", "2.0");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/license", "LGPL with exception");
		m->declare("signal.lib/name", "Faust Signal Routing Library");
		m->declare("signal.lib/version", "0.0");
		m->declare("route.lib/name", "Faust Signal Routing Library");
		m->declare("route.lib/version", "0.0");
		m->declare("delay.lib/name", "Faust Delay Library");
		m->declare("delay.lib/version", "0.0");
		m->declare("basic.lib/name", "Faust Basic Element Library");
		m->declare("basic.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 1; }
	virtual int getNumOutputs() { return 2; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(1.92e+05f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (6.2831855f / fConst0);
		fConst2 = (6.2831855f / float(fConst0));
		fConst3 = floorf(((0.153129f * fConst0) + 0.5f));
		fConst4 = ((0 - (6.9077554f * fConst3)) / fConst0);
		fConst5 = (3.1415927f / fConst0);
		fConst6 = floorf(((0.020346f * fConst0) + 0.5f));
		iConst7 = int((int((fConst3 - fConst6)) & 8191));
		fConst8 = (0.001f * fConst0);
		iConst9 = int((int((fConst6 + -1)) & 1023));
		fConst10 = floorf(((0.174713f * fConst0) + 0.5f));
		fConst11 = ((0 - (6.9077554f * fConst10)) / fConst0);
		fConst12 = floorf(((0.022904f * fConst0) + 0.5f));
		iConst13 = int((int((fConst10 - fConst12)) & 8191));
		iConst14 = int((int((fConst12 + -1)) & 2047));
		fConst15 = floorf(((0.127837f * fConst0) + 0.5f));
		fConst16 = ((0 - (6.9077554f * fConst15)) / fConst0);
		fConst17 = floorf(((0.031604f * fConst0) + 0.5f));
		iConst18 = int((int((fConst15 - fConst17)) & 8191));
		iConst19 = int((int((fConst17 + -1)) & 2047));
		fConst20 = floorf(((0.125f * fConst0) + 0.5f));
		fConst21 = ((0 - (6.9077554f * fConst20)) / fConst0);
		fConst22 = floorf(((0.013458f * fConst0) + 0.5f));
		iConst23 = int((int((fConst20 - fConst22)) & 8191));
		iConst24 = int((int((fConst22 + -1)) & 1023));
		fConst25 = floorf(((0.210389f * fConst0) + 0.5f));
		fConst26 = ((0 - (6.9077554f * fConst25)) / fConst0);
		fConst27 = floorf(((0.024421f * fConst0) + 0.5f));
		iConst28 = int((int((fConst25 - fConst27)) & 16383));
		iConst29 = int((int((fConst27 + -1)) & 2047));
		fConst30 = floorf(((0.192303f * fConst0) + 0.5f));
		fConst31 = ((0 - (6.9077554f * fConst30)) / fConst0);
		fConst32 = floorf(((0.029291f * fConst0) + 0.5f));
		iConst33 = int((int((fConst30 - fConst32)) & 8191));
		iConst34 = int((int((fConst32 + -1)) & 2047));
		fConst35 = floorf(((0.256891f * fConst0) + 0.5f));
		fConst36 = ((0 - (6.9077554f * fConst35)) / fConst0);
		fConst37 = floorf(((0.027333f * fConst0) + 0.5f));
		iConst38 = int((int((fConst35 - fConst37)) & 16383));
		iConst39 = int((int((fConst37 + -1)) & 2047));
		fConst40 = floorf(((0.219991f * fConst0) + 0.5f));
		fConst41 = ((0 - (6.9077554f * fConst40)) / fConst0);
		fConst42 = floorf(((0.019123f * fConst0) + 0.5f));
		iConst43 = int((int((fConst40 - fConst42)) & 16383));
		iConst44 = int((int((fConst42 + -1)) & 1023));
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.0f;
		fslider1 = 315.0f;
		fslider2 = 6e+03f;
		fslider3 = 2.0f;
		fslider4 = 3.0f;
		fslider5 = 2e+02f;
		fslider6 = 6e+01f;
		fslider7 = 0.0f;
		fslider8 = 1.5e+03f;
		fslider9 = 0.0f;
		fslider10 = -2e+01f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		IOTA = 0;
		for (int i=0; i<8192; i++) fVec0[i] = 0;
		for (int i=0; i<8192; i++) fVec1[i] = 0;
		for (int i=0; i<1024; i++) fVec2[i] = 0;
		for (int i=0; i<2; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<8192; i++) fVec3[i] = 0;
		for (int i=0; i<2048; i++) fVec4[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<8192; i++) fVec5[i] = 0;
		for (int i=0; i<2048; i++) fVec6[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec24[i] = 0;
		for (int i=0; i<2; i++) fRec23[i] = 0;
		for (int i=0; i<8192; i++) fVec7[i] = 0;
		for (int i=0; i<1024; i++) fVec8[i] = 0;
		for (int i=0; i<2; i++) fRec21[i] = 0;
		for (int i=0; i<2; i++) fRec28[i] = 0;
		for (int i=0; i<2; i++) fRec27[i] = 0;
		for (int i=0; i<16384; i++) fVec9[i] = 0;
		for (int i=0; i<2048; i++) fVec10[i] = 0;
		for (int i=0; i<2; i++) fRec25[i] = 0;
		for (int i=0; i<2; i++) fRec32[i] = 0;
		for (int i=0; i<2; i++) fRec31[i] = 0;
		for (int i=0; i<8192; i++) fVec11[i] = 0;
		for (int i=0; i<2048; i++) fVec12[i] = 0;
		for (int i=0; i<2; i++) fRec29[i] = 0;
		for (int i=0; i<2; i++) fRec36[i] = 0;
		for (int i=0; i<2; i++) fRec35[i] = 0;
		for (int i=0; i<16384; i++) fVec13[i] = 0;
		for (int i=0; i<2048; i++) fVec14[i] = 0;
		for (int i=0; i<2; i++) fRec33[i] = 0;
		for (int i=0; i<2; i++) fRec40[i] = 0;
		for (int i=0; i<2; i++) fRec39[i] = 0;
		for (int i=0; i<16384; i++) fVec15[i] = 0;
		for (int i=0; i<1024; i++) fVec16[i] = 0;
		for (int i=0; i<2; i++) fRec37[i] = 0;
		for (int i=0; i<3; i++) fRec1[i] = 0;
		for (int i=0; i<3; i++) fRec2[i] = 0;
		for (int i=0; i<3; i++) fRec3[i] = 0;
		for (int i=0; i<3; i++) fRec4[i] = 0;
		for (int i=0; i<3; i++) fRec5[i] = 0;
		for (int i=0; i<3; i++) fRec6[i] = 0;
		for (int i=0; i<3; i++) fRec7[i] = 0;
		for (int i=0; i<3; i++) fRec8[i] = 0;
		for (int i=0; i<3; i++) fRec0[i] = 0;
		for (int i=0; i<3; i++) fRec41[i] = 0;
		for (int i=0; i<2; i++) fRec42[i] = 0;
		for (int i=0; i<2; i++) fRec43[i] = 0;
		for (int i=0; i<3; i++) fRec44[i] = 0;
		for (int i=0; i<3; i++) fRec45[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	virtual reverb* clone() {
		return new reverb();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->declare(0, "0", "");
		ui_interface->declare(0, "tooltip", "~ ZITA REV1 FEEDBACK DELAY NETWORK (FDN) & SCHROEDER       ALLPASS-COMB REVERBERATOR (8x8). See Faust's reverb.lib for documentation and       references");
		ui_interface->openHorizontalBox("Zita_Rev1");
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("Input");
		ui_interface->declare(&fslider6, "1", "");
		ui_interface->declare(&fslider6, "style", "knob");
		ui_interface->declare(&fslider6, "tooltip", "Delay in ms    before reverberation begins");
		ui_interface->declare(&fslider6, "unit", "ms");
		ui_interface->addVerticalSlider("In Delay", &fslider6, 6e+01f, 2e+01f, 1e+02f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "2", "");
		ui_interface->openHorizontalBox("Decay Times in Bands (see tooltips)");
		ui_interface->declare(&fslider5, "1", "");
		ui_interface->declare(&fslider5, "scale", "log");
		ui_interface->declare(&fslider5, "style", "knob");
		ui_interface->declare(&fslider5, "tooltip", "Crossover frequency (Hz) separating low and middle frequencies");
		ui_interface->declare(&fslider5, "unit", "Hz");
		ui_interface->addVerticalSlider("LF X", &fslider5, 2e+02f, 5e+01f, 1e+03f, 1.0f);
		ui_interface->declare(&fslider4, "2", "");
		ui_interface->declare(&fslider4, "scale", "log");
		ui_interface->declare(&fslider4, "style", "knob");
		ui_interface->declare(&fslider4, "tooltip", "T60 = time (in seconds) to decay 60dB in low-frequency band");
		ui_interface->declare(&fslider4, "unit", "s");
		ui_interface->addVerticalSlider("Low RT60", &fslider4, 3.0f, 1.0f, 8.0f, 0.1f);
		ui_interface->declare(&fslider3, "3", "");
		ui_interface->declare(&fslider3, "scale", "log");
		ui_interface->declare(&fslider3, "style", "knob");
		ui_interface->declare(&fslider3, "tooltip", "T60 = time (in seconds) to decay 60dB in middle band");
		ui_interface->declare(&fslider3, "unit", "s");
		ui_interface->addVerticalSlider("Mid RT60", &fslider3, 2.0f, 1.0f, 8.0f, 0.1f);
		ui_interface->declare(&fslider2, "4", "");
		ui_interface->declare(&fslider2, "scale", "log");
		ui_interface->declare(&fslider2, "style", "knob");
		ui_interface->declare(&fslider2, "tooltip", "Frequency (Hz) at which the high-frequency T60 is half the middle-band's T60");
		ui_interface->declare(&fslider2, "unit", "Hz");
		ui_interface->addVerticalSlider("HF Damping", &fslider2, 6e+03f, 1.5e+03f, 2.352e+04f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "3", "");
		ui_interface->openHorizontalBox("RM Peaking Equalizer 1");
		ui_interface->declare(&fslider1, "1", "");
		ui_interface->declare(&fslider1, "scale", "log");
		ui_interface->declare(&fslider1, "style", "knob");
		ui_interface->declare(&fslider1, "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 1");
		ui_interface->declare(&fslider1, "unit", "Hz");
		ui_interface->addVerticalSlider("Eq1 Freq", &fslider1, 315.0f, 4e+01f, 2.5e+03f, 1.0f);
		ui_interface->declare(&fslider0, "2", "");
		ui_interface->declare(&fslider0, "style", "knob");
		ui_interface->declare(&fslider0, "tooltip", "Peak level    in dB of second-order Regalia-Mitra peaking equalizer section 1");
		ui_interface->declare(&fslider0, "unit", "dB");
		ui_interface->addVerticalSlider("Eq1 Level", &fslider0, 0.0f, -15.0f, 15.0f, 0.1f);
		ui_interface->closeBox();
		ui_interface->declare(0, "4", "");
		ui_interface->openHorizontalBox("RM Peaking Equalizer 2");
		ui_interface->declare(&fslider8, "1", "");
		ui_interface->declare(&fslider8, "scale", "log");
		ui_interface->declare(&fslider8, "style", "knob");
		ui_interface->declare(&fslider8, "tooltip", "Center-frequency of second-order Regalia-Mitra peaking equalizer section 2");
		ui_interface->declare(&fslider8, "unit", "Hz");
		ui_interface->addVerticalSlider("Eq2 Freq", &fslider8, 1.5e+03f, 1.6e+02f, 1e+04f, 1.0f);
		ui_interface->declare(&fslider7, "2", "");
		ui_interface->declare(&fslider7, "style", "knob");
		ui_interface->declare(&fslider7, "tooltip", "Peak level    in dB of second-order Regalia-Mitra peaking equalizer section 2");
		ui_interface->declare(&fslider7, "unit", "dB");
		ui_interface->addVerticalSlider("Eq2 Level", &fslider7, 0.0f, -15.0f, 15.0f, 0.1f);
		ui_interface->closeBox();
		ui_interface->declare(0, "5", "");
		ui_interface->openHorizontalBox("Output");
		ui_interface->declare(&fslider9, "1", "");
		ui_interface->declare(&fslider9, "style", "knob");
		ui_interface->declare(&fslider9, "tooltip", "-1 = dry, 1 = wet");
		ui_interface->addVerticalSlider("Dry/Wet Mix", &fslider9, 0.0f, -1.0f, 1.0f, 0.01f);
		ui_interface->declare(&fslider10, "2", "");
		ui_interface->declare(&fslider10, "style", "knob");
		ui_interface->declare(&fslider10, "tooltip", "Output scale    factor");
		ui_interface->declare(&fslider10, "unit", "dB");
		ui_interface->addVerticalSlider("Level", &fslider10, -2e+01f, -7e+01f, 4e+01f, 0.1f);
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		float 	fSlow0 = powf(10,(0.05f * float(fslider0)));
		float 	fSlow1 = float(fslider1);
		float 	fSlow2 = (fConst1 * (fSlow1 / sqrtf(max((float)0, fSlow0))));
		float 	fSlow3 = ((1.0f - fSlow2) / (fSlow2 + 1.0f));
		float 	fSlow4 = ((0 - cosf((fConst1 * fSlow1))) * (fSlow3 + 1));
		float 	fSlow5 = cosf((fConst2 * float(fslider2)));
		float 	fSlow6 = float(fslider3);
		float 	fSlow7 = expf((fConst4 / fSlow6));
		float 	fSlow8 = faustpower<2>(fSlow7);
		float 	fSlow9 = (1.0f - (fSlow5 * fSlow8));
		float 	fSlow10 = (1.0f - fSlow8);
		float 	fSlow11 = (fSlow9 / fSlow10);
		float 	fSlow12 = sqrtf(max((float)0, ((faustpower<2>(fSlow9) / faustpower<2>(fSlow10)) + -1.0f)));
		float 	fSlow13 = (fSlow11 - fSlow12);
		float 	fSlow14 = (fSlow7 * (fSlow12 + (1.0f - fSlow11)));
		float 	fSlow15 = float(fslider4);
		float 	fSlow16 = ((expf((fConst4 / fSlow15)) / fSlow7) + -1);
		float 	fSlow17 = (1.0f / tanf((fConst5 * float(fslider5))));
		float 	fSlow18 = (fSlow17 + 1);
		float 	fSlow19 = (1.0f / fSlow18);
		float 	fSlow20 = (0 - ((1 - fSlow17) / fSlow18));
		int 	iSlow21 = int((int((fConst8 * float(fslider6))) & 8191));
		float 	fSlow22 = expf((fConst11 / fSlow6));
		float 	fSlow23 = faustpower<2>(fSlow22);
		float 	fSlow24 = (1.0f - (fSlow5 * fSlow23));
		float 	fSlow25 = (1.0f - fSlow23);
		float 	fSlow26 = (fSlow24 / fSlow25);
		float 	fSlow27 = sqrtf(max((float)0, ((faustpower<2>(fSlow24) / faustpower<2>(fSlow25)) + -1.0f)));
		float 	fSlow28 = (fSlow26 - fSlow27);
		float 	fSlow29 = (fSlow22 * (fSlow27 + (1.0f - fSlow26)));
		float 	fSlow30 = ((expf((fConst11 / fSlow15)) / fSlow22) + -1);
		float 	fSlow31 = expf((fConst16 / fSlow6));
		float 	fSlow32 = faustpower<2>(fSlow31);
		float 	fSlow33 = (1.0f - (fSlow5 * fSlow32));
		float 	fSlow34 = (1.0f - fSlow32);
		float 	fSlow35 = (fSlow33 / fSlow34);
		float 	fSlow36 = sqrtf(max((float)0, ((faustpower<2>(fSlow33) / faustpower<2>(fSlow34)) + -1.0f)));
		float 	fSlow37 = (fSlow35 - fSlow36);
		float 	fSlow38 = (fSlow31 * (fSlow36 + (1.0f - fSlow35)));
		float 	fSlow39 = ((expf((fConst16 / fSlow15)) / fSlow31) + -1);
		float 	fSlow40 = expf((fConst21 / fSlow6));
		float 	fSlow41 = faustpower<2>(fSlow40);
		float 	fSlow42 = (1.0f - (fSlow5 * fSlow41));
		float 	fSlow43 = (1.0f - fSlow41);
		float 	fSlow44 = (fSlow42 / fSlow43);
		float 	fSlow45 = sqrtf(max((float)0, ((faustpower<2>(fSlow42) / faustpower<2>(fSlow43)) + -1.0f)));
		float 	fSlow46 = (fSlow44 - fSlow45);
		float 	fSlow47 = (fSlow40 * (fSlow45 + (1.0f - fSlow44)));
		float 	fSlow48 = ((expf((fConst21 / fSlow15)) / fSlow40) + -1);
		float 	fSlow49 = expf((fConst26 / fSlow6));
		float 	fSlow50 = faustpower<2>(fSlow49);
		float 	fSlow51 = (1.0f - (fSlow5 * fSlow50));
		float 	fSlow52 = (1.0f - fSlow50);
		float 	fSlow53 = (fSlow51 / fSlow52);
		float 	fSlow54 = sqrtf(max((float)0, ((faustpower<2>(fSlow51) / faustpower<2>(fSlow52)) + -1.0f)));
		float 	fSlow55 = (fSlow53 - fSlow54);
		float 	fSlow56 = (fSlow49 * (fSlow54 + (1.0f - fSlow53)));
		float 	fSlow57 = ((expf((fConst26 / fSlow15)) / fSlow49) + -1);
		float 	fSlow58 = expf((fConst31 / fSlow6));
		float 	fSlow59 = faustpower<2>(fSlow58);
		float 	fSlow60 = (1.0f - (fSlow5 * fSlow59));
		float 	fSlow61 = (1.0f - fSlow59);
		float 	fSlow62 = (fSlow60 / fSlow61);
		float 	fSlow63 = sqrtf(max((float)0, ((faustpower<2>(fSlow60) / faustpower<2>(fSlow61)) + -1.0f)));
		float 	fSlow64 = (fSlow62 - fSlow63);
		float 	fSlow65 = (fSlow58 * (fSlow63 + (1.0f - fSlow62)));
		float 	fSlow66 = ((expf((fConst31 / fSlow15)) / fSlow58) + -1);
		float 	fSlow67 = expf((fConst36 / fSlow6));
		float 	fSlow68 = faustpower<2>(fSlow67);
		float 	fSlow69 = (1.0f - (fSlow5 * fSlow68));
		float 	fSlow70 = (1.0f - fSlow68);
		float 	fSlow71 = (fSlow69 / fSlow70);
		float 	fSlow72 = sqrtf(max((float)0, ((faustpower<2>(fSlow69) / faustpower<2>(fSlow70)) + -1.0f)));
		float 	fSlow73 = (fSlow71 - fSlow72);
		float 	fSlow74 = (fSlow67 * (fSlow72 + (1.0f - fSlow71)));
		float 	fSlow75 = ((expf((fConst36 / fSlow15)) / fSlow67) + -1);
		float 	fSlow76 = expf((fConst41 / fSlow6));
		float 	fSlow77 = faustpower<2>(fSlow76);
		float 	fSlow78 = (1.0f - (fSlow77 * fSlow5));
		float 	fSlow79 = (1.0f - fSlow77);
		float 	fSlow80 = (fSlow78 / fSlow79);
		float 	fSlow81 = sqrtf(max((float)0, ((faustpower<2>(fSlow78) / faustpower<2>(fSlow79)) + -1.0f)));
		float 	fSlow82 = (fSlow80 - fSlow81);
		float 	fSlow83 = (fSlow76 * (fSlow81 + (1.0f - fSlow80)));
		float 	fSlow84 = ((expf((fConst41 / fSlow15)) / fSlow76) + -1);
		float 	fSlow85 = powf(10,(0.05f * float(fslider7)));
		float 	fSlow86 = float(fslider8);
		float 	fSlow87 = (fConst1 * (fSlow86 / sqrtf(max((float)0, fSlow85))));
		float 	fSlow88 = ((1.0f - fSlow87) / (fSlow87 + 1.0f));
		float 	fSlow89 = ((0 - cosf((fConst1 * fSlow86))) * (fSlow88 + 1));
		float 	fSlow90 = (0.001f * float(fslider9));
		float 	fSlow91 = (0.001f * powf(10,(0.05f * float(fslider10))));
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		FAUSTFLOAT* output1 = output[1];
		for (int i=0; i<count; i++) {
			fRec12[0] = ((fSlow19 * (fRec1[1] + fRec1[2])) + (fSlow20 * fRec12[1]));
			fRec11[0] = ((fSlow13 * fRec11[1]) + (fSlow14 * (fRec1[1] + (fSlow16 * fRec12[0]))));
			fVec0[IOTA&8191] = ((0.35355338f * fRec11[0]) + 1e-20f);
			float fTemp0 = (float)input0[i];
			fVec1[IOTA&8191] = fTemp0;
			float fTemp1 = (0.3f * fVec1[(IOTA-iSlow21)&8191]);
			float fTemp2 = ((fVec0[(IOTA-iConst7)&8191] + fTemp1) - (0.6f * fRec9[1]));
			fVec2[IOTA&1023] = fTemp2;
			fRec9[0] = fVec2[(IOTA-iConst9)&1023];
			float 	fRec10 = (0.6f * fVec2[IOTA&1023]);
			fRec16[0] = ((fSlow19 * (fRec5[1] + fRec5[2])) + (fSlow20 * fRec16[1]));
			fRec15[0] = ((fSlow28 * fRec15[1]) + (fSlow29 * (fRec5[1] + (fSlow30 * fRec16[0]))));
			fVec3[IOTA&8191] = ((0.35355338f * fRec15[0]) + 1e-20f);
			float fTemp3 = ((fVec3[(IOTA-iConst13)&8191] + fTemp1) - (0.6f * fRec13[1]));
			fVec4[IOTA&2047] = fTemp3;
			fRec13[0] = fVec4[(IOTA-iConst14)&2047];
			float 	fRec14 = (0.6f * fVec4[IOTA&2047]);
			fRec20[0] = ((fSlow19 * (fRec3[1] + fRec3[2])) + (fSlow20 * fRec20[1]));
			fRec19[0] = ((fSlow37 * fRec19[1]) + (fSlow38 * (fRec3[1] + (fSlow39 * fRec20[0]))));
			fVec5[IOTA&8191] = ((0.35355338f * fRec19[0]) + 1e-20f);
			float fTemp4 = (fVec5[(IOTA-iConst18)&8191] - ((0.6f * fRec17[1]) + fTemp1));
			fVec6[IOTA&2047] = fTemp4;
			fRec17[0] = fVec6[(IOTA-iConst19)&2047];
			float 	fRec18 = (0.6f * fVec6[IOTA&2047]);
			fRec24[0] = ((fSlow19 * (fRec7[1] + fRec7[2])) + (fSlow20 * fRec24[1]));
			fRec23[0] = ((fSlow46 * fRec23[1]) + (fSlow47 * (fRec7[1] + (fSlow48 * fRec24[0]))));
			fVec7[IOTA&8191] = ((0.35355338f * fRec23[0]) + 1e-20f);
			float fTemp5 = (fVec7[(IOTA-iConst23)&8191] - ((0.6f * fRec21[1]) + fTemp1));
			fVec8[IOTA&1023] = fTemp5;
			fRec21[0] = fVec8[(IOTA-iConst24)&1023];
			float 	fRec22 = (0.6f * fVec8[IOTA&1023]);
			fRec28[0] = ((fSlow19 * (fRec2[1] + fRec2[2])) + (fSlow20 * fRec28[1]));
			fRec27[0] = ((fSlow55 * fRec27[1]) + (fSlow56 * (fRec2[1] + (fSlow57 * fRec28[0]))));
			fVec9[IOTA&16383] = ((0.35355338f * fRec27[0]) + 1e-20f);
			float fTemp6 = (((0.6f * fRec25[1]) + fVec9[(IOTA-iConst28)&16383]) + fTemp1);
			fVec10[IOTA&2047] = fTemp6;
			fRec25[0] = fVec10[(IOTA-iConst29)&2047];
			float 	fRec26 = (0 - (0.6f * fVec10[IOTA&2047]));
			fRec32[0] = ((fSlow19 * (fRec6[1] + fRec6[2])) + (fSlow20 * fRec32[1]));
			fRec31[0] = ((fSlow64 * fRec31[1]) + (fSlow65 * (fRec6[1] + (fSlow66 * fRec32[0]))));
			fVec11[IOTA&8191] = ((0.35355338f * fRec31[0]) + 1e-20f);
			float fTemp7 = (((0.6f * fRec29[1]) + fVec11[(IOTA-iConst33)&8191]) + fTemp1);
			fVec12[IOTA&2047] = fTemp7;
			fRec29[0] = fVec12[(IOTA-iConst34)&2047];
			float 	fRec30 = (0 - (0.6f * fVec12[IOTA&2047]));
			fRec36[0] = ((fSlow19 * (fRec4[1] + fRec4[2])) + (fSlow20 * fRec36[1]));
			fRec35[0] = ((fSlow73 * fRec35[1]) + (fSlow74 * (fRec4[1] + (fSlow75 * fRec36[0]))));
			fVec13[IOTA&16383] = ((0.35355338f * fRec35[0]) + 1e-20f);
			float fTemp8 = (((0.6f * fRec33[1]) + fVec13[(IOTA-iConst38)&16383]) - fTemp1);
			fVec14[IOTA&2047] = fTemp8;
			fRec33[0] = fVec14[(IOTA-iConst39)&2047];
			float 	fRec34 = (0 - (0.6f * fVec14[IOTA&2047]));
			fRec40[0] = ((fSlow19 * (fRec8[1] + fRec8[2])) + (fSlow20 * fRec40[1]));
			fRec39[0] = ((fSlow82 * fRec39[1]) + (fSlow83 * (fRec8[1] + (fSlow84 * fRec40[0]))));
			fVec15[IOTA&16383] = ((0.35355338f * fRec39[0]) + 1e-20f);
			float fTemp9 = (((0.6f * fRec37[1]) + fVec15[(IOTA-iConst43)&16383]) - fTemp1);
			fVec16[IOTA&1023] = fTemp9;
			fRec37[0] = fVec16[(IOTA-iConst44)&1023];
			float 	fRec38 = (0 - (0.6f * fVec16[IOTA&1023]));
			float fTemp10 = (fRec37[1] + fRec38);
			float fTemp11 = (fRec34 + (fRec33[1] + fTemp10));
			float fTemp12 = (fRec26 + (fRec25[1] + (fRec30 + (fRec29[1] + fTemp11))));
			fRec1[0] = (fRec10 + (fRec9[1] + (fRec14 + (fRec13[1] + (fRec18 + (fRec17[1] + (fRec22 + (fRec21[1] + fTemp12))))))));
			fRec2[0] = ((fRec10 + (fRec9[1] + (fRec14 + (fRec13[1] + (fRec18 + (fRec17[1] + (fRec21[1] + fRec22))))))) - fTemp12);
			float fTemp13 = (fRec26 + (fRec25[1] + (fRec29[1] + fRec30)));
			fRec3[0] = ((fRec10 + (fRec9[1] + (fRec14 + (fRec13[1] + fTemp13)))) - (fRec18 + (fRec17[1] + (fRec22 + (fRec21[1] + fTemp11)))));
			fRec4[0] = ((fRec10 + (fRec9[1] + (fRec14 + (fRec13[1] + fTemp11)))) - (fRec18 + (fRec17[1] + (fRec22 + (fRec21[1] + fTemp13)))));
			float fTemp14 = (fRec33[1] + fRec34);
			float fTemp15 = (fRec26 + (fRec25[1] + fTemp14));
			float fTemp16 = (fRec30 + (fRec29[1] + fTemp10));
			fRec5[0] = ((fRec10 + (fRec9[1] + (fRec18 + (fRec17[1] + fTemp15)))) - (fRec14 + (fRec13[1] + (fRec22 + (fRec21[1] + fTemp16)))));
			fRec6[0] = ((fRec10 + (fRec9[1] + (fRec18 + (fRec17[1] + fTemp16)))) - (fRec14 + (fRec13[1] + (fRec22 + (fRec21[1] + fTemp15)))));
			float fTemp17 = ((fRec25[1] + fTemp10) + fRec26);
			float fTemp18 = (fRec30 + (fRec29[1] + fTemp14));
			fRec7[0] = (((((fTemp17 + fRec21[1]) + fRec22) + fRec9[1]) + fRec10) - ((((fRec17[1] + fTemp18) + fRec18) + fRec13[1]) + fRec14));
			fRec8[0] = (((((fRec21[1] + fTemp18) + fRec22) + fRec9[1]) + fRec10) - ((((fTemp17 + fRec17[1]) + fRec18) + fRec13[1]) + fRec14));
			float fTemp19 = (0.37f * (fRec2[0] + fRec3[0]));
			float fTemp20 = (fSlow4 * fRec0[1]);
			fRec0[0] = (fTemp19 - (fTemp20 + (fSlow3 * fRec0[2])));
			float fTemp21 = (fSlow3 * fRec0[0]);
			float fTemp22 = (0.5f * (((((fSlow0 * (((fTemp20 + fRec0[2]) + fTemp21) - fTemp19)) + fTemp20) + fRec0[2]) + fTemp19) + fTemp21));
			float fTemp23 = (fSlow89 * fRec41[1]);
			fRec41[0] = (fTemp22 - (fTemp23 + (fSlow88 * fRec41[2])));
			float fTemp24 = (fSlow88 * fRec41[0]);
			fRec42[0] = (fSlow90 + (0.999f * fRec42[1]));
			float fTemp25 = (fRec42[0] + 1.0f);
			float fTemp26 = (1.0f - (0.5f * fTemp25));
			float fTemp27 = (fTemp25 * fVec1[IOTA&8191]);
			fRec43[0] = (fSlow91 + (0.999f * fRec43[1]));
			output0[i] = (FAUSTFLOAT)(0.5f * (((((((fTemp22 + (fSlow85 * (((fTemp23 + fRec41[2]) + fTemp24) - fTemp22))) + fTemp23) + fRec41[2]) + fTemp24) * fTemp26) + fTemp27) * fRec43[0]));
			float fTemp28 = (0.37f * (fRec2[0] - fRec3[0]));
			float fTemp29 = (fSlow4 * fRec44[1]);
			fRec44[0] = (fTemp28 - (fTemp29 + (fSlow3 * fRec44[2])));
			float fTemp30 = (fSlow3 * fRec44[0]);
			float fTemp31 = (fTemp29 + fRec44[2]);
			float fTemp32 = (0.5f * ((fTemp30 + (fTemp28 + fTemp31)) + (fSlow0 * ((fTemp30 + fTemp31) - fTemp28))));
			float fTemp33 = (fSlow89 * fRec45[1]);
			fRec45[0] = (fTemp32 - (fTemp33 + (fSlow88 * fRec45[2])));
			float fTemp34 = ((fSlow88 * fRec45[0]) + (fTemp33 + fRec45[2]));
			output1[i] = (FAUSTFLOAT)(0.5f * (fRec43[0] * (fTemp27 + (fTemp26 * ((fTemp32 + fTemp34) + (fSlow85 * (fTemp34 - fTemp32)))))));
			// post processing
			fRec45[2] = fRec45[1]; fRec45[1] = fRec45[0];
			fRec44[2] = fRec44[1]; fRec44[1] = fRec44[0];
			fRec43[1] = fRec43[0];
			fRec42[1] = fRec42[0];
			fRec41[2] = fRec41[1]; fRec41[1] = fRec41[0];
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
			fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
			fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
			fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
			fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
			fRec37[1] = fRec37[0];
			fRec39[1] = fRec39[0];
			fRec40[1] = fRec40[0];
			fRec33[1] = fRec33[0];
			fRec35[1] = fRec35[0];
			fRec36[1] = fRec36[0];
			fRec29[1] = fRec29[0];
			fRec31[1] = fRec31[0];
			fRec32[1] = fRec32[0];
			fRec25[1] = fRec25[0];
			fRec27[1] = fRec27[0];
			fRec28[1] = fRec28[0];
			fRec21[1] = fRec21[0];
			fRec23[1] = fRec23[0];
			fRec24[1] = fRec24[0];
			fRec17[1] = fRec17[0];
			fRec19[1] = fRec19[0];
			fRec20[1] = fRec20[0];
			fRec13[1] = fRec13[0];
			fRec15[1] = fRec15[0];
			fRec16[1] = fRec16[0];
			fRec9[1] = fRec9[0];
			IOTA = IOTA+1;
			fRec11[1] = fRec11[0];
			fRec12[1] = fRec12[0];
		}
	}
};


