#pragma once
#ifndef __PROPERTY_SET_HPP__
#define __PROPERTY_SET_HPP__

#include "wxDefs.hpp"
#include "Robotarium.hpp"

using namespace Robotarium;


class wxVec3
{
public:
    wxVec3()
    {
        x = y = z = 0.0;
    }
    wxVec3( double _x, double _y, double _z )
    {
        x = _x; y = _y; z = _z;
    }

    double x, y, z;
};

inline bool operator == (const wxVec3& a, const wxVec3& b)
{
    return (a.x == b.x && a.y == b.y && a.z == b.z);
}

WX_PG_DECLARE_VARIANT_DATA(wxVec3)



class wxScrew
{
public:
    wxScrew()
    {
        Sx = Sy = Sz = Theta = 0.0;
    }
    wxScrew( double _Sx, double _Sy, double _Sz, double _Theta )
    {
        Sx = _Sx; Sy = _Sy; Sz = _Sz; Theta = _Theta;
    }

    double Sx, Sy, Sz, Theta;
};

inline bool operator == (const wxScrew& a, const wxScrew& b)
{
	return (a.Sx == b.Sx && a.Sy == b.Sy && a.Sz == b.Sz && a.Theta == b.Theta);
}

WX_PG_DECLARE_VARIANT_DATA(wxScrew)






class Vec3Property : public wxPGProperty
{
    WX_PG_DECLARE_PROPERTY_CLASS(Vec3Property)
public:

    Vec3Property( const wxString& label = wxPG_LABEL, const wxString& name = wxPG_LABEL,
                     const wxVec3& value = wxVec3() );
    virtual ~Vec3Property();

    virtual wxVariant ChildChanged( wxVariant& thisValue,
                                    int childIndex,
                                    wxVariant& childValue ) const;
    virtual void RefreshChildren();

protected:
};


class ScrewProperty : public wxPGProperty
{
    WX_PG_DECLARE_PROPERTY_CLASS(ScrewProperty)
public:

    ScrewProperty( const wxString& label = wxPG_LABEL, const wxString& name = wxPG_LABEL,
                     const wxScrew& value = wxScrew() );
    virtual ~ScrewProperty();

    virtual wxVariant ChildChanged( wxVariant& thisValue,
                                    int childIndex,
                                    wxVariant& childValue ) const;
    virtual void RefreshChildren();

protected:
};


class LookAtPointProperty : public wxPGProperty
{
    WX_PG_DECLARE_PROPERTY_CLASS(LookAtPointProperty )
public:

    LookAtPointProperty ( const wxString& label = wxPG_LABEL, const wxString& name = wxPG_LABEL,
                     const wxVec3& value = wxVec3() );

    virtual ~LookAtPointProperty ();

    virtual wxVariant ChildChanged( wxVariant& thisValue,
                                    int childIndex,
                                    wxVariant& childValue ) const;
    virtual void RefreshChildren();

protected:
};

#endif