// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"

#include <bullet/src/btBulletDynamicsCommon.h>

#include <moai-bullet/MOAIBulletBody.h>
#include <moai-bullet/MOAIBulletJoint.h>
#include <moai-bullet/MOAIBulletWorld.h>
#include <moai-bullet/MOAIBulletJointFreedom.h>
//----------------------------------------------------------------//
int MOAIBulletJointFreedom::_setLinLimit ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletJoint, "UNN" )
	float unitsToMeters = self->GetUnitsToMeters ();
	if ( !self->mJoint ) {
		MOAILog ( state, MOAILogMessages::MOAIBox2DJoint_MissingInstance );
		return 0;
	}	
	float lower = state.GetValue < float >( 2, 0.0f );	
	float upper = state.GetValue < float >( 3, 0.0f );	
	btGeneric6DofConstraint* joint = ( btGeneric6DofConstraint* )self->mJoint;
	//joint->setLowerLinLimit(lower);
	//joint->setUpperLinLimit(upper);	
	//state.Push ( 1 );	
	return 1;
}

//----------------------------------------------------------------//
int MOAIBulletJointFreedom::_setAngLimit ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletJoint, "UNN" )
	float unitsToMeters = self->GetUnitsToMeters ();
	if ( !self->mJoint ) {
		MOAILog ( state, MOAILogMessages::MOAIBox2DJoint_MissingInstance );
		return 0;
	}	
	float lower = state.GetValue < float >( 2, 0.0f );	
	float upper = state.GetValue < float >( 3, 0.0f );	
	btGeneric6DofConstraint* joint = ( btGeneric6DofConstraint* )self->mJoint;	
	//joint->setLowerAngLimit(-SIMD_PI / lower);
	//joint->setUpperAngLimit( SIMD_PI / upper);	
	//state.Push ( 1 );
	return 1;
}
//----------------------------------------------------------------//
MOAIBulletJointFreedom::MOAIBulletJointFreedom () {	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAIBulletJoint )
	RTTI_END
}
//----------------------------------------------------------------//
MOAIBulletJointFreedom::~MOAIBulletJointFreedom () {
}
//----------------------------------------------------------------//
void MOAIBulletJointFreedom::RegisterLuaClass ( MOAILuaState& state ) {
	MOAIBulletJoint::RegisterLuaClass ( state );
}
//----------------------------------------------------------------//
void MOAIBulletJointFreedom::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAIBulletJoint::RegisterLuaFuncs ( state );

	luaL_Reg regTable [] = {		
		{ "setLinLimit",					_setLinLimit}, 
		{ "setAngLimit",					_setAngLimit}, 
		{ NULL, NULL },
	};	
	luaL_register ( state, 0, regTable );
}
