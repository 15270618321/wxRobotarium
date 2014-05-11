#include "PropertySet.hpp"


Vec3 toRobotarium(wxVec3& _vec)
{
	return Vec3(_vec.x, _vec.y, _vec.z);
}


Quat toRobotarium(wxScrew& _screw)
{
	return Quat(Radian(_screw.Theta), Vec3(_screw.Sx, _screw.Sy, _screw.Sz));
}


WX_PG_IMPLEMENT_VARIANT_DATA_DUMMY_EQ(wxVec3)

	WX_PG_IMPLEMENT_PROPERTY_CLASS(Vec3Property,wxPGProperty,
	wxVec3,const wxVec3&,TextCtrl)


	Vec3Property::Vec3Property( const wxString& label, 
	const wxString& name,
	const wxVec3& value) 
	: wxPGProperty(label,name)
{
	SetValue(WXVARIANT(value));
	AddPrivateChild( new wxFloatProperty(wxT("X"),wxPG_LABEL,value.x) );
	AddPrivateChild( new wxFloatProperty(wxT("Y"),wxPG_LABEL,value.y) );
	AddPrivateChild( new wxFloatProperty(wxT("Z"),wxPG_LABEL,value.z) );
}

Vec3Property::~Vec3Property() { }

void Vec3Property::RefreshChildren()
{
	if ( !GetChildCount() ) return;
	const wxVec3& point = wxVec3RefFromVariant(m_value);
	Item(0)->SetValue( point.x );
	Item(1)->SetValue( point.y );
	Item(2)->SetValue( point.z );
}

wxVariant Vec3Property::ChildChanged( wxVariant& thisValue,
	int childIndex,
	wxVariant& childValue ) const
{

	wxVec3 vector;
	vector << thisValue;

	switch ( childIndex )
	{
	case 0: vector.x = childValue.GetDouble(); break;
	case 1: vector.y = childValue.GetDouble(); break;
	case 2: vector.z = childValue.GetDouble(); break;
	}

	wxVariant newVariant;
	newVariant << vector;

	switch(((PropertyGrid *)this->GetGrid())->mCurrentNode->GetNodeType())
	{
	case Robotarium::SCENE_NODE_TYPE :
		boost::static_pointer_cast<Robotarium::graphic::SceneNode>
			(((PropertyGrid *)this->GetGrid())->mCurrentNode)->SetPosition(toRobotarium(vector));
		break;
	case Robotarium::CAMERA_SCENE_NODE_TYPE :
		boost::static_pointer_cast<Robotarium::graphic::CameraSceneNode>
			(((PropertyGrid *)this->GetGrid())->mCurrentNode)->SetPosition(toRobotarium(vector));
		break;
	}


	return newVariant;
}










WX_PG_IMPLEMENT_VARIANT_DATA_DUMMY_EQ(wxScrew)

	WX_PG_IMPLEMENT_PROPERTY_CLASS(ScrewProperty,wxPGProperty,
	wxScrew,const wxScrew&,TextCtrl)


	ScrewProperty::ScrewProperty( const wxString& label, 
	const wxString& name,
	const wxScrew& value) 
	: wxPGProperty(label,name)
{
	SetValue(WXVARIANT(value));
	AddPrivateChild( new wxFloatProperty(wxT("Sx"),wxPG_LABEL,value.Sx) );
	AddPrivateChild( new wxFloatProperty(wxT("Sy"),wxPG_LABEL,value.Sy) );
	AddPrivateChild( new wxFloatProperty(wxT("Sz"),wxPG_LABEL,value.Sz) );
	AddPrivateChild( new wxFloatProperty(wxT("Theta"),wxPG_LABEL,value.Theta) );
}

ScrewProperty::~ScrewProperty() { }

void ScrewProperty::RefreshChildren()
{
	if ( !GetChildCount() ) return;
	const wxScrew& screw = wxScrewRefFromVariant(m_value);
	Item(0)->SetValue( screw.Sx );
	Item(1)->SetValue( screw.Sy );
	Item(2)->SetValue( screw.Sz );
	Item(3)->SetValue( screw.Theta );
}

wxVariant ScrewProperty::ChildChanged( wxVariant& thisValue,
	int childIndex,
	wxVariant& childValue ) const
{

	wxScrew vector;
	vector << thisValue;

	switch ( childIndex )
	{
	case 0: vector.Sx = childValue.GetDouble(); break;
	case 1: vector.Sy = childValue.GetDouble(); break;
	case 2: vector.Sz = childValue.GetDouble(); break;
	case 3: vector.Theta = childValue.GetDouble(); break;
	}

	wxVariant newVariant;
	newVariant << vector;

	switch(((PropertyGrid *)this->GetGrid())->mCurrentNode->GetNodeType())
	{
	case Robotarium::SCENE_NODE_TYPE :
		boost::static_pointer_cast<Robotarium::graphic::SceneNode>
			(((PropertyGrid *)this->GetGrid())->mCurrentNode)->SetOrientation(toRobotarium(vector));
		break;
	case Robotarium::CAMERA_SCENE_NODE_TYPE :
		boost::static_pointer_cast<Robotarium::graphic::CameraSceneNode>
			(((PropertyGrid *)this->GetGrid())->mCurrentNode)->SetOrientation(toRobotarium(vector));
		break;
	}


	return newVariant;
}






WX_PG_IMPLEMENT_PROPERTY_CLASS(LookAtPointProperty,wxPGProperty,
	wxVec3,const wxVec3&,TextCtrl)


LookAtPointProperty::LookAtPointProperty( const wxString& label, 
	const wxString& name,
	const wxVec3& value) 
	: wxPGProperty(label,name)
{
	SetValue(WXVARIANT(value));
	AddPrivateChild( new wxFloatProperty(wxT("X"),wxPG_LABEL,value.x) );
	AddPrivateChild( new wxFloatProperty(wxT("Y"),wxPG_LABEL,value.y) );
	AddPrivateChild( new wxFloatProperty(wxT("Z"),wxPG_LABEL,value.z) );
}

LookAtPointProperty::~LookAtPointProperty() { }

void LookAtPointProperty::RefreshChildren()
{
	if ( !GetChildCount() ) return;
	const wxVec3& LAP = wxVec3RefFromVariant(m_value);
	Item(0)->SetValue( LAP.x );
	Item(1)->SetValue( LAP.y );
	Item(2)->SetValue( LAP.z );
}

wxVariant LookAtPointProperty::ChildChanged( wxVariant& thisValue,
	int childIndex,
	wxVariant& childValue ) const
{

	wxVec3 vector;
	vector << thisValue;

	switch ( childIndex )
	{
	case 0: vector.x = childValue.GetDouble(); break;
	case 1: vector.y = childValue.GetDouble(); break;
	case 2: vector.z = childValue.GetDouble(); break;
	}

	wxVariant newVariant;
	newVariant << vector;

	switch(((PropertyGrid *)this->GetGrid())->mCurrentNode->GetNodeType())
	{
	case Robotarium::CAMERA_SCENE_NODE_TYPE :
		boost::static_pointer_cast<Robotarium::graphic::CameraSceneNode>
			(((PropertyGrid *)this->GetGrid())->mCurrentNode)->SetLookAtPoint(toRobotarium(vector));
		break;
	}


	return newVariant;
}
