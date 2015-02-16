#include "pch.h"


//I THINK I NEED TO MAKE VERY MANUAL

//1. HOW TO REMOVE JOINTS ???
//2. HOW TO ADD JOINTS ???
//3. WHY ARE PLANES ON RIGID BODIES THEY NEED TO BE JUST SHAPES ???

// NEW BODY  ?
// NEW SHAPE ?
// body add shape
// 



//WILL ADD TO LUA ? OT FIELDS PERHAPS? OR WORLD
//#define ACTIVE_TAG 1
//#define ISLAND_SLEEPING 2
//#define WANTS_DEACTIVATION 3
//#define DISABLE_DEACTIVATION 4
//#define DISABLE_SIMULATION 5







//#include <bullet/src/btBulletDynamicsCommon.h>
//#include "btRigidBodyWithCollisionEvents.h"

//#include "bullet/src/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.h"
//#include "bullet/src/BulletCollision/CollisionShapes/btBoxShape.h"
//#include "bullet/src/BulletCollision/NarrowPhaseCollision/btGjkPairDetector.h"
//#include "bullet/src/BulletCollision/NarrowPhaseCollision/btPointCollector.h"
//#include "bullet/src/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.h"
//#include "bullet/src/BulletCollision/NarrowPhaseCollision/btConvexPenetrationDepthSolver.h"
//#include "bullet/src/BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.h"

////*********************************************
//struct bulletObject{
//        int id;
//        float r,g,b;
//        bool hit;
//        btRigidBody* body;
//        bulletObject(btRigidBody* b,int i,float r0,float g0,float b0) : body(b),id(i),r(r0),g(g0),b(b0),hit(false) {}
//};
////*********************************************
//bool MOAIBulletWorld::callbackFunc(btManifoldPoint& cp,const btCollisionObject* obj1,int id1,int index1,const btCollisionObject* obj2,int id2,int index2)
//{
//        ((bulletObject*)obj1->getUserPointer())->hit=true;       
//       ((bulletObject*)obj2->getUserPointer())->hit=true;
//        return false;
//}
//








//WTF
#include <bullet/src/LinearMath/btQuickprof.h>



#include <moai-bullet/MOAIBulletWorld.h>
#include <moai-bullet/MOAIBulletDebugDraw.h>
#include <moai-bullet/MOAIBulletBody.h>
#include <moai-bullet/MOAIBulletShape.h>

#include <moai-bullet/MOAIBulletJoint.h>
#include <moai-bullet/MOAIBulletJointCone.h>
#include <moai-bullet/MOAIBulletJointFixed.h>
#include <moai-bullet/MOAIBulletJointFreedom.h>
#include <moai-bullet/MOAIBulletJointHinge.h>
#include <moai-bullet/MOAIBulletJointPoint.h>
#include <moai-bullet/MOAIBulletJointSlide.h>
#include <moai-bullet/MOAIBulletTransform.h>

// CProfileManager()
//THIS CALLBACKS DON' WORK I DON' UNDERSTAND
//#include "btRigidBodyWithCollisionEvents.h"
//btRigidBody* g_StaticGroundBox = NULL;
// ICollisionInterface
//void  MOAIBulletWorld::OnCollisionStart(btRigidBodyWithEvents* thisBodyA,btCollisionObject* bodyB,const btVector3& localSpaceContactPoint,const btVector3& worldSpaceContactPoint,const btVector3& worldSpaceContactNormal,const btScalar penetrationDistance,const btScalar appliedImpulse)	{
//	printf("COLLID MOTHER FUCKER A\n");
//}
//void  MOAIBulletWorld::OnCollisionContinue(btRigidBodyWithEvents* thisBodyA,btCollisionObject* bodyB,const btVector3& localSpaceContactPoint,const btVector3& worldSpaceContactPoint,const btVector3& worldSpaceContactNormal,const btScalar penetrationDistance,const btScalar appliedImpulse)	{
//	//printf("Collision Continue: %s - %s\n",thisBodyA!=g_StaticGroundBox ? thisBodyA->getCollisionShape()->getName() : "g_StaticGroundBox",bodyB!=g_StaticGroundBox ? bodyB->getCollisionShape()->getName() : "g_StaticGroundBox" );
//	printf("COLLID MOTHER FUCKER D\n");
//}
//void  MOAIBulletWorld::OnCollisionStop(btRigidBodyWithEvents* thisBodyA,btCollisionObject* bodyB,const btVector3& localSpaceContactPoint,const btVector3& worldSpaceContactPoint,const btVector3& worldSpaceContactNormal,const btScalar penetrationDistance,const btScalar appliedImpulse)	{
//	//printf("Collision End: %s - %s\n",thisBodyA!=g_StaticGroundBox ? thisBodyA->getCollisionShape()->getName() : "g_StaticGroundBox",bodyB!=g_StaticGroundBox ? bodyB->getCollisionShape()->getName() : "g_StaticGroundBox" );
//	printf("COLLID MOTHER FUCKER C\n");
//}




//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
// TEST CODE
#define ENABLE_ALL_DEMOS 1
#define CUBE_HALF_EXTENTS 1.f
#define SIMD_PI_2 ((SIMD_PI)*0.5f)
#define SIMD_PI_4 ((SIMD_PI)*0.25f)
#define M_PI_8 0.5 * M_PI_4


btRigidBody* MOAIBulletWorld::localCreateRigidBody (btScalar mass, const btTransform& startTransform, btCollisionShape* shape)
{
		btVector3 localInertia(1,0,0);
		shape->calculateLocalInertia(1,localInertia);
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,shape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);
		return body;


}


//****************************************************************//
int MOAIBulletWorld::_testJoint ( lua_State* L ) {

		MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )	
		printf("TESTING : FIXED JOINT \n");

		btCollisionShape* shapeA = new btBoxShape(btVector3(.5,.5,.5));
		btCollisionShape* shapeB = new btBoxShape(btVector3(.5,.5,.5));
				
		btTransform transA;
		transA.setIdentity();
		transA.setOrigin(btVector3(0,0,0));

		btTransform transB;
		transB.setIdentity();
		transB.setOrigin(btVector3(0,0,0));

		float mass = 1.0f;
		btTransform tr;
		tr.setIdentity();
		tr.setOrigin(btVector3(btScalar(0), btScalar(0), btScalar(0)));
		tr.getBasis().setEulerZYX(0,0,0);	
		btRigidBody* pBodyA = self->localCreateRigidBody( 0.0, transA, shapeA);			
		self->mWorld->addRigidBody(pBodyA);


		tr.setIdentity();
		tr.setOrigin(btVector3(btScalar(0), btScalar(0), btScalar(0)));
		tr.getBasis().setEulerZYX(0,0,0);
		btRigidBody* pBodyB = self->localCreateRigidBody(mass, transB, shapeB);		
		self->mWorld->addRigidBody(pBodyB);

		btTransform frameInA;
		frameInA = btTransform::getIdentity();
		frameInA.getBasis().setEulerZYX(0, 0, 0);
		frameInA.setOrigin(btVector3(btScalar(0.), btScalar(0), btScalar(0.)));

		btTransform	frameInB;
		frameInB = btTransform::getIdentity();
		frameInB.getBasis().setEulerZYX(0,0, 0);
		frameInB.setOrigin(btVector3(btScalar(0.), btScalar(0), btScalar(0.)));

		btFixedConstraint*	btJoint = new btFixedConstraint(*pBodyA, *pBodyB, frameInA, frameInB);	

		self->mWorld->addConstraint(btJoint, true);
		btJoint->setDbgDrawSize(btScalar(1.f));		


	return 0;
}

//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************
//**************************************************************************************************************

int MOAIBulletWorld::_testRagDoll ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletWorld, "UNNN" )

	enum
{
BODYPART_PELVIS = 0,
BODYPART_SPINE,
BODYPART_HEAD,
BODYPART_LEFT_UPPER_LEG,
BODYPART_LEFT_LOWER_LEG,
BODYPART_RIGHT_UPPER_LEG,
BODYPART_RIGHT_LOWER_LEG,
BODYPART_LEFT_UPPER_ARM,
BODYPART_LEFT_LOWER_ARM,
BODYPART_RIGHT_UPPER_ARM,
BODYPART_RIGHT_LOWER_ARM,
BODYPART_COUNT
};
enum
{
JOINT_PELVIS_SPINE = 0,
JOINT_SPINE_HEAD,
JOINT_LEFT_HIP,
JOINT_LEFT_KNEE,
JOINT_RIGHT_HIP,
JOINT_RIGHT_KNEE,
JOINT_LEFT_SHOULDER,
JOINT_LEFT_ELBOW,
JOINT_RIGHT_SHOULDER,
JOINT_RIGHT_ELBOW,
JOINT_COUNT
};


float offsetX = state.GetValue < float >( 2, 0.0f );
float offsetY = state.GetValue < float >( 3, 0.0f );
float offsetZ = state.GetValue < float >( 4, 0.0f );

printf("TESTING : RAGDOLL %f %f %f\n",offsetX,offsetY,offsetZ);


btCollisionShape*	m_shapes[BODYPART_COUNT];
btRigidBody*		m_bodies[BODYPART_COUNT];
btTypedConstraint*	m_joints[JOINT_COUNT];


//******************************************************************************************
// Setup the geometry
	m_shapes[BODYPART_PELVIS]			= new btCapsuleShape(btScalar(0.15), btScalar(0.20));
	m_shapes[BODYPART_SPINE]			= new btCapsuleShape(btScalar(0.15), btScalar(0.28));
	m_shapes[BODYPART_HEAD]				= new btCapsuleShape(btScalar(0.10), btScalar(0.05));
	m_shapes[BODYPART_LEFT_UPPER_LEG]	= new btCapsuleShape(btScalar(0.07), btScalar(0.45));
	m_shapes[BODYPART_LEFT_LOWER_LEG]	= new btCapsuleShape(btScalar(0.05), btScalar(0.37));
	m_shapes[BODYPART_RIGHT_UPPER_LEG]	= new btCapsuleShape(btScalar(0.07), btScalar(0.45));
	m_shapes[BODYPART_RIGHT_LOWER_LEG]	= new btCapsuleShape(btScalar(0.05), btScalar(0.37));
	m_shapes[BODYPART_LEFT_UPPER_ARM]	= new btCapsuleShape(btScalar(0.05), btScalar(0.33));
	m_shapes[BODYPART_LEFT_LOWER_ARM]	= new btCapsuleShape(btScalar(0.04), btScalar(0.25));
	m_shapes[BODYPART_RIGHT_UPPER_ARM]	= new btCapsuleShape(btScalar(0.05), btScalar(0.33));
	m_shapes[BODYPART_RIGHT_LOWER_ARM]	= new btCapsuleShape(btScalar(0.04), btScalar(0.25));


//**********************************************************************************
// Setup all the rigid bodies
btTransform offset; 
offset.setIdentity();
offset.setOrigin(btVector3 ( offsetX,offsetY,offsetZ));

//TRANSFORM
btTransform transform;
transform.setIdentity();
//**********************************************************************************

transform.setOrigin(btVector3(btScalar(0.), btScalar(1), btScalar(0.)));
m_bodies[BODYPART_PELVIS] = self->localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_PELVIS]);
self->mWorld->addRigidBody(m_bodies[BODYPART_PELVIS]);






//**********************************************************************************

transform.setIdentity();
transform.setOrigin(btVector3(btScalar(0.), btScalar(1.2), btScalar(0.)));
m_bodies[BODYPART_SPINE] = self->localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_SPINE]);



self->mWorld->addRigidBody(m_bodies[BODYPART_SPINE]);





//**********************************************************************************
transform.setIdentity();
transform.setOrigin(btVector3(btScalar(0.), btScalar(1.6), btScalar(0.)));
m_bodies[BODYPART_HEAD] = self->localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_HEAD]);
self->mWorld->addRigidBody(m_bodies[BODYPART_HEAD]);


//**********************************************************************************
transform.setIdentity();
transform.setOrigin(btVector3(btScalar(-0.18), btScalar(0.65), btScalar(0.)));
m_bodies[BODYPART_LEFT_UPPER_LEG] = self->localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEFT_UPPER_LEG]);

self->mWorld->addRigidBody(m_bodies[BODYPART_LEFT_UPPER_LEG]);


//**********************************************************************************
transform.setIdentity();
transform.setOrigin(btVector3(btScalar(-0.18), btScalar(0.2), btScalar(0.)));
m_bodies[BODYPART_LEFT_LOWER_LEG] = self->localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEFT_LOWER_LEG]);
self->mWorld->addRigidBody(m_bodies[BODYPART_LEFT_LOWER_LEG]);


//**********************************************************************************
transform.setIdentity();
transform.setOrigin(btVector3(btScalar(0.18), btScalar(0.65), btScalar(0.)));
m_bodies[BODYPART_RIGHT_UPPER_LEG] = self->localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_RIGHT_UPPER_LEG]);
self->mWorld->addRigidBody(m_bodies[BODYPART_RIGHT_UPPER_LEG]);

//**********************************************************************************
transform.setIdentity();
transform.setOrigin(btVector3(btScalar(0.18), btScalar(0.2), btScalar(0.)));
m_bodies[BODYPART_RIGHT_LOWER_LEG] = self->localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_RIGHT_LOWER_LEG]);
self->mWorld->addRigidBody(m_bodies[BODYPART_RIGHT_LOWER_LEG]);

//**********************************************************************************
transform.setIdentity();
transform.setOrigin(btVector3(btScalar(-0.35), btScalar(1.45), btScalar(0.)));
transform.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(M_PI_2));
m_bodies[BODYPART_LEFT_UPPER_ARM] = self->localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEFT_UPPER_ARM]);
self->mWorld->addRigidBody(m_bodies[BODYPART_LEFT_UPPER_ARM]);

//**********************************************************************************
transform.setIdentity();
transform.setOrigin(btVector3(btScalar(-0.7), btScalar(1.45), btScalar(0.)));
transform.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(M_PI_2));
m_bodies[BODYPART_LEFT_LOWER_ARM] = self->localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_LEFT_LOWER_ARM]);
self->mWorld->addRigidBody(m_bodies[BODYPART_LEFT_LOWER_ARM]);

//**********************************************************************************
transform.setIdentity();
transform.setOrigin(btVector3(btScalar(0.35), btScalar(1.45), btScalar(0.)));
transform.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(-M_PI_2));
m_bodies[BODYPART_RIGHT_UPPER_ARM] = self->localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_RIGHT_UPPER_ARM]);
self->mWorld->addRigidBody(m_bodies[BODYPART_RIGHT_UPPER_ARM]);

//**********************************************************************************
transform.setIdentity();
transform.setOrigin(btVector3(btScalar(0.7), btScalar(1.45), btScalar(0.)));
transform.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(-M_PI_2));
m_bodies[BODYPART_RIGHT_LOWER_ARM] = self->localCreateRigidBody(btScalar(1.), offset*transform, m_shapes[BODYPART_RIGHT_LOWER_ARM]);
self->mWorld->addRigidBody(m_bodies[BODYPART_RIGHT_LOWER_ARM]);







//*******************************************************************************************
// Setup some damping on the m_bodies
		//for (int i = 0; i < BODYPART_COUNT; ++i)
		//{
		//		m_bodies[i]->setDamping(0.05, 0.85);
		//		m_bodies[i]->setDeactivationTime(0.8);
		//		m_bodies[i]->setSleepingThresholds(1.6, 2.5);
		//}


//****************************************************************************************
//****************************************************************************************

btHingeConstraint*		hingeC;
btConeTwistConstraint*	coneC;

btTransform localA; 
btTransform	localB;

float joint_draw = 0.1f;
//****************************************************************************************
//****************************************************************************************
localA.setIdentity(); 
localB.setIdentity();

localA.getBasis().setEulerZYX(0,0,0); 
localA.setOrigin(btVector3(btScalar(0.), btScalar(0.15), btScalar(0.)));

localB.getBasis().setEulerZYX(0,0,0); 
localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.15), btScalar(0.)));

hingeC = new btHingeConstraint(*m_bodies[BODYPART_PELVIS], *m_bodies[BODYPART_SPINE], localA, localB);
hingeC->setLimit(btScalar(-M_PI_4), btScalar(M_PI_2));
hingeC->setDbgDrawSize(joint_draw);
m_joints[JOINT_PELVIS_SPINE] = hingeC;	

self->mWorld->addConstraint(m_joints[JOINT_PELVIS_SPINE], true);
//
////****************************************************************************************
////****************************************************************************************
localA.setIdentity(); 
localB.setIdentity();
localA.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(M_PI_2)); localA.setOrigin(btVector3(btScalar(0.), btScalar(0.30), btScalar(0.)));
localB.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(M_PI_2)); localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.14), btScalar(0.)));

coneC = new btConeTwistConstraint(*m_bodies[BODYPART_SPINE], *m_bodies[BODYPART_HEAD], localA, localB);
coneC->setLimit(btScalar(M_PI_4), btScalar(M_PI_4), btScalar(M_PI_2));
coneC->setDbgDrawSize(joint_draw);
m_joints[JOINT_SPINE_HEAD] = coneC;

self->mWorld->addConstraint(m_joints[JOINT_SPINE_HEAD], true);
//
////****************************************************************************************
////****************************************************************************************
//
localA.setIdentity(); 
localA.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(-M_PI_4*5)); localA.setOrigin(btVector3(btScalar(-0.18), btScalar(-0.10), btScalar(0.)));

localB.setIdentity();
localB.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(-M_PI_4*5)); localB.setOrigin(btVector3(btScalar(0.), btScalar(0.225), btScalar(0.)));

coneC = new btConeTwistConstraint(*m_bodies[BODYPART_PELVIS], *m_bodies[BODYPART_LEFT_UPPER_LEG], localA, localB);
coneC->setLimit(btScalar(M_PI_4), btScalar(M_PI_4), btScalar(0));
coneC->setDbgDrawSize(joint_draw);
m_joints[JOINT_LEFT_HIP] = coneC;
	
self->mWorld->addConstraint(m_joints[JOINT_LEFT_HIP], true);

//****************************************************************************************
//****************************************************************************************

localA.setIdentity(); 
localA.getBasis().setEulerZYX(btScalar(0),btScalar(M_PI_2),btScalar(0)); localA.setOrigin(btVector3(btScalar(0.), btScalar(-0.225), btScalar(0.)));

localB.setIdentity();
localB.getBasis().setEulerZYX(btScalar(0),btScalar(M_PI_2),btScalar(0)); localB.setOrigin(btVector3(btScalar(0.), btScalar(0.185), btScalar(0.)));

hingeC = new btHingeConstraint(*m_bodies[BODYPART_LEFT_UPPER_LEG], *m_bodies[BODYPART_LEFT_LOWER_LEG], localA, localB);
hingeC->setLimit(btScalar(0), btScalar(M_PI_2));
hingeC->setDbgDrawSize(joint_draw);
m_joints[JOINT_LEFT_KNEE] = hingeC;	

self->mWorld->addConstraint(m_joints[JOINT_LEFT_KNEE], true);

//****************************************************************************************
//****************************************************************************************
localA.setIdentity(); 
localA.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(M_PI_4)); localA.setOrigin(btVector3(btScalar(0.18), btScalar(-0.10), btScalar(0.)));
localB.setIdentity();
localB.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(M_PI_4)); localB.setOrigin(btVector3(btScalar(0.), btScalar(0.225), btScalar(0.)));

coneC = new btConeTwistConstraint(*m_bodies[BODYPART_PELVIS], *m_bodies[BODYPART_RIGHT_UPPER_LEG], localA, localB);
coneC->setLimit(btScalar(M_PI_4), btScalar(M_PI_4), btScalar(0));
coneC->setDbgDrawSize(joint_draw);
m_joints[JOINT_RIGHT_HIP] = coneC;

self->mWorld->addConstraint(m_joints[JOINT_RIGHT_HIP], true);

//****************************************************************************************
//****************************************************************************************
localA.setIdentity(); 
localA.getBasis().setEulerZYX(btScalar(0),btScalar(M_PI_2),btScalar(0)); localA.setOrigin(btVector3(btScalar(0.), btScalar(-0.225), btScalar(0.)));

localB.setIdentity();
localB.getBasis().setEulerZYX(btScalar(0),btScalar(M_PI_2),btScalar(0));localB.setOrigin(btVector3(btScalar(0.), btScalar(0.185), btScalar(0.)));

hingeC = new btHingeConstraint(*m_bodies[BODYPART_RIGHT_UPPER_LEG], *m_bodies[BODYPART_RIGHT_LOWER_LEG], localA, localB);
hingeC->setLimit(btScalar(0), btScalar(M_PI_2));
hingeC->setDbgDrawSize(joint_draw);
m_joints[JOINT_RIGHT_KNEE] = hingeC;


self->mWorld->addConstraint(m_joints[JOINT_RIGHT_KNEE], true);
//****************************************************************************************
//****************************************************************************************
localA.setIdentity();
localA.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(M_PI)); localA.setOrigin(btVector3(btScalar(-0.2), btScalar(0.15), btScalar(0.)));

localB.setIdentity();
localB.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(M_PI_2)); localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.18), btScalar(0.)));

coneC = new btConeTwistConstraint(*m_bodies[BODYPART_SPINE], *m_bodies[BODYPART_LEFT_UPPER_ARM], localA, localB);
coneC->setLimit(btScalar(M_PI_2), btScalar(M_PI_2), btScalar(0));
coneC->setDbgDrawSize(joint_draw);
m_joints[JOINT_LEFT_SHOULDER] = coneC;

self->mWorld->addConstraint(m_joints[JOINT_LEFT_SHOULDER], true);

//****************************************************************************************
//****************************************************************************************
localA.setIdentity(); 
localA.getBasis().setEulerZYX(btScalar(0),btScalar(M_PI_2),btScalar(0)); localA.setOrigin(btVector3(btScalar(0.), btScalar(0.18), btScalar(0.)));

localB.setIdentity();
localB.getBasis().setEulerZYX(btScalar(0),btScalar(M_PI_2),btScalar(0));localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.14), btScalar(0.)));

hingeC = new btHingeConstraint(*m_bodies[BODYPART_LEFT_UPPER_ARM], *m_bodies[BODYPART_LEFT_LOWER_ARM], localA, localB);
hingeC->setLimit(btScalar(0), btScalar(M_PI_2));
hingeC->setDbgDrawSize(joint_draw);
m_joints[JOINT_LEFT_ELBOW] = hingeC;

self->mWorld->addConstraint(m_joints[JOINT_LEFT_ELBOW], true);

//****************************************************************************************
//****************************************************************************************
localA.setIdentity(); 

localA.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(0)); localA.setOrigin(btVector3(btScalar(0.2), btScalar(0.15), btScalar(0.)));
localB.setIdentity();
localB.getBasis().setEulerZYX(btScalar(0),btScalar(0),btScalar(M_PI_2)); localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.18), btScalar(0.)));

coneC = new btConeTwistConstraint(*m_bodies[BODYPART_SPINE], *m_bodies[BODYPART_RIGHT_UPPER_ARM], localA, localB);
coneC->setLimit(btScalar(M_PI_2), btScalar(M_PI_2), btScalar(0));
coneC->setDbgDrawSize(joint_draw);
m_joints[JOINT_RIGHT_SHOULDER] = coneC;

self->mWorld->addConstraint(m_joints[JOINT_RIGHT_SHOULDER], true);

//****************************************************************************************
//****************************************************************************************

localA.setIdentity();
localA.getBasis().setEulerZYX(btScalar(0),btScalar(M_PI_2),btScalar(0)); 
localA.setOrigin(btVector3(btScalar(0.), btScalar(0.18), btScalar(0.)));

localB.setIdentity();
localB.getBasis().setEulerZYX(btScalar(0),btScalar(M_PI_2),btScalar(0));
localB.setOrigin(btVector3(btScalar(0.), btScalar(-0.14), btScalar(0.)));

hingeC = new btHingeConstraint(*m_bodies[BODYPART_RIGHT_UPPER_ARM], *m_bodies[BODYPART_RIGHT_LOWER_ARM], localA, localB);
hingeC->setLimit(btScalar(0), btScalar(M_PI_2));
hingeC->setDbgDrawSize(joint_draw);
m_joints[JOINT_RIGHT_ELBOW] = hingeC;

self->mWorld->addConstraint(m_joints[JOINT_RIGHT_ELBOW], true);


return 1;

};


//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
//************************************************************************************************************
///CAR

//TEMP GLOBAL
btRaycastVehicle	*m_vehicle;
btRigidBody			*m_carChassis;

//WTF ????
//btScalar suspensionRestLength(0.6);
float suspensionRestLength = 0.6f;

float	gEngineForce			= 00.f;
float	gBreakingForce			= 00.f;
float	maxEngineForce			= 1000.f;//this should be engine/velocity dependent
float	maxBreakingForce		= 100.f;
float	gVehicleSteering		= 0.f;
float	steeringIncrement		= 0.01f;
float	steeringClamp			= 0.3f;
float	wheelRadius				= 0.7f;
float	wheelWidth				= 0.4f;
float	wheelFriction			= 1000;//BT_LARGE_FLOAT;
float	suspensionStiffness		= 20.f;
float	suspensionDamping		= 2.3f;
float	suspensionCompression	= 4.4f;
float	rollInfluence			= 0.1f;//1.0f;

btVector3 wheelDirectionCS0(0,-1,0);
btVector3 wheelAxleCS(-1,0,0);

//--------------------------------------------------------------------//
int MOAIBulletWorld::_testCar ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )

btCollisionShape*	chassisShape = new btBoxShape(btVector3(1.f,0.5f,2.f));
btCompoundShape*	compound	 = new btCompoundShape();

//****************************************************
//SHAPE
btTransform localTrans;
localTrans.setIdentity();
localTrans.getBasis().setEulerZYX(0,0,0);
localTrans.setOrigin(btVector3(0,1,0));	
compound->addChildShape(localTrans,chassisShape);


//********************************************************
//BODY 
btTransform tr;
tr.setIdentity();
tr.getBasis().setEulerZYX(0,0,0);
tr.setOrigin(btVector3(0,0,0));
m_carChassis = self->localCreateRigidBody(0,tr,compound); //MASS 300 or 800


//SET IT TO THE WORLD
	self->mWorld->addRigidBody(m_carChassis);

		{

			//MAKE A RAY CAST
			btVehicleRaycaster* m_vehicleRayCaster  = new btDefaultVehicleRaycaster(self->mWorld);
			//TUNE IT
			btRaycastVehicle::btVehicleTuning m_tuning;

					//m_tuning.m_frictionSlip			= 0;
					//m_tuning.m_maxSuspensionForce		= 0;
					//m_tuning.m_maxSuspensionTravelCm	= 0;
					//m_tuning.m_suspensionCompression	= 0;
					//m_tuning.m_suspensionDamping		= 0;
					//m_tuning.m_suspensionStiffness	= 0;


			//MAKE A VEHICLE : TUNE : BODY : CASTER
			m_vehicle			= new btRaycastVehicle(m_tuning,m_carChassis,m_vehicleRayCaster);	
			m_carChassis->setActivationState(DISABLE_DEACTIVATION);	



			// MAKE JOINTS
			btVector3 connectionPointCS0;
			float connectionHeight	= 1.2f;
			bool  isFrontWheel		= false;	

			//***********************	
			connectionPointCS0= btVector3(btScalar(CUBE_HALF_EXTENTS-(0.3*wheelWidth)),btScalar(connectionHeight),btScalar(2*CUBE_HALF_EXTENTS-wheelRadius));
			m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);
			//***********************
			connectionPointCS0 = btVector3(btScalar(-CUBE_HALF_EXTENTS+(0.3*wheelWidth)),btScalar(connectionHeight),btScalar(2*CUBE_HALF_EXTENTS-wheelRadius));
			m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);
			//***********************
			connectionPointCS0 = btVector3(btScalar(-CUBE_HALF_EXTENTS+(0.3*wheelWidth)),btScalar(connectionHeight),btScalar(-2*CUBE_HALF_EXTENTS+wheelRadius));	
			m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);
			//***********************
			connectionPointCS0 = btVector3(btScalar(CUBE_HALF_EXTENTS-(0.3*wheelWidth)),btScalar(connectionHeight),btScalar(-2*CUBE_HALF_EXTENTS+wheelRadius));
			m_vehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_tuning,isFrontWheel);
			
			//*************************************************************************
			//*************************************************************************

					//for (int i=0;i<m_vehicle->getNumWheels();i++)
					//{
					//	btWheelInfo& wheel = m_vehicle->getWheelInfo(i);
					//	wheel.m_suspensionStiffness			= suspensionStiffness;
					//	wheel.m_wheelsDampingRelaxation		= suspensionDamping;
					//	wheel.m_wheelsDampingCompression	= suspensionCompression;
					//	wheel.m_frictionSlip				= wheelFriction;
					//	wheel.m_rollInfluence				= rollInfluence;
					//	//wheel.
					//}




			//SET VIEHICLE TO WORLD
			self->mWorld->addVehicle(m_vehicle);		

			//SET CORDINATES ON VEICL
			int rightIndex   = 0;
			int upIndex		 = 1;
			int forwardIndex = 2;			
			m_vehicle->setCoordinateSystem(rightIndex,upIndex,forwardIndex);

					//m_tuning.m_frictionSlip			= 0;
					//m_tuning.m_maxSuspensionForce		= 0;
					//m_tuning.m_maxSuspensionTravelCm	= 0;
					//m_tuning.m_suspensionCompression	= 0;
					//m_tuning.m_suspensionDamping		= 0;
					//m_tuning.m_suspensionStiffness	= 0;




		}

return 1;
};
//------------------------------------------------------------///
int MOAIBulletWorld::_testCarUpdate ( lua_State* L ) {
MOAI_LUA_SETUP ( MOAIBulletWorld, "UN" )	

int dir = state.GetValue < int >( 2, 0 );

if (dir == 5) {	
	gVehicleSteering = 0;
};

//UP
if (dir == 1) {	
	gEngineForce = maxEngineForce;
	gBreakingForce = 0.f;
};
//RIGHT
if (dir == 4) {	
	gVehicleSteering += steeringIncrement;
	if ( gVehicleSteering > steeringClamp) 
	gVehicleSteering = steeringClamp;
};
//DOWN
if (dir == 3) {	
	gBreakingForce = maxBreakingForce;
	gEngineForce = 0.f;
};
//LEFT
if (dir == 2) {	
	gVehicleSteering -= steeringIncrement;
	if ( gVehicleSteering < -steeringClamp)
	gVehicleSteering = -steeringClamp;
}


	btTransform chassisWorldTrans;
	//look at the vehicle
	m_carChassis->getMotionState()->getWorldTransform(chassisWorldTrans);
	btVector3 m_cameraTargetPosition = chassisWorldTrans.getOrigin();
	

	btQuaternion rotation =chassisWorldTrans.getRotation();
	float quaternion_x = rotation.x();
	float quaternion_y = rotation.y();		
	float quaternion_z = rotation.z();

	//printf("%f \n",quaternion_x);
	//**************************************************************************************************************
	int wheelIndex;


//BRAKING

	//********************************
		wheelIndex = 3;
		m_vehicle->applyEngineForce(gEngineForce,wheelIndex);
		m_vehicle->setBrake(gBreakingForce,wheelIndex);
	//********************************
		wheelIndex = 2;
		m_vehicle->applyEngineForce(gEngineForce,wheelIndex);
		m_vehicle->setBrake(gBreakingForce,wheelIndex);




//STEARING
	//********************************
				wheelIndex = 1;
				m_vehicle->setSteeringValue(gVehicleSteering,wheelIndex);
	//********************************
				wheelIndex = 4;
				m_vehicle->setSteeringValue(gVehicleSteering,wheelIndex);


		//LOC
		lua_pushnumber ( state, m_cameraTargetPosition.getX() ); 
		lua_pushnumber ( state, m_cameraTargetPosition.getY() ); 
		lua_pushnumber ( state, m_cameraTargetPosition.getZ() ); 
		//ROT
		lua_pushnumber ( state, quaternion_x ); 
		lua_pushnumber ( state, quaternion_y ); 
		lua_pushnumber ( state, quaternion_z ); 
		
		return 6;

};






//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************
//***************************************************************************************************************************













//----------------------------------------------------------------//
float MOAIBulletPrim::GetUnitsToMeters () {
	if ( this->mWorld ) {
		//NO DONE
	}
	return 1.0f;
}
//----------------------------------------------------------------//
MOAIBulletPrim::MOAIBulletPrim () :
	mWorld ( 0 ),
	mDestroy ( false ),
	mDestroyNext ( 0 ) {
}
//----------------------------------------------------------------//
bool MOAIBulletWorld::IsDone () {
	return false;
}
//----------------------------------------------------------------//
// COLLISION CALL BACK SHOULD BE IN IT OWN FILE
// HAS ISSUE WITH ALWASY BUMPPING PLANES
struct YourOwnFilterCallback : public btOverlapFilterCallback
{
	virtual bool	needBroadphaseCollision(btBroadphaseProxy* proxy0,btBroadphaseProxy* proxy1) const
	{
		bool collides = (proxy0->m_collisionFilterGroup & proxy1->m_collisionFilterMask) != 0;
		collides = collides && (proxy1->m_collisionFilterGroup & proxy0->m_collisionFilterMask);	

			btCollisionObject* colObj0 = static_cast<btCollisionObject*>(proxy0->m_clientObject);
			btCollisionObject* colObj1 = static_cast<btCollisionObject*>(proxy1->m_clientObject);
			
			//PREVENT COLLIDING WITH SELF
			if (colObj1 == colObj0) {
				return collides;
			};		






			////LOOK : THE PLANE THE PLANE THE FUCKING PLANE
			btCompoundShape *shapeA = (btCompoundShape *)colObj0->getCollisionShape();
			btCompoundShape *shapeB = (btCompoundShape *)colObj1->getCollisionShape();	

			btRigidBody* rigBodyA = ( btRigidBody* )colObj0;
			MOAIBulletBody* moaiBodyA = ( MOAIBulletBody* )rigBodyA->getUserPointer (); 	

			btRigidBody* rigBodyB = ( btRigidBody* )colObj1;
			MOAIBulletBody* moaiBodyB = ( MOAIBulletBody* )rigBodyB->getUserPointer ();

			if ((moaiBodyA) && (moaiBodyB)) {		
				//printf("ass \n");

				//MOAI BODIES ARE COMMPOUND SHAPES
				//DON"T RETURN PLANE COLLISION MAYBE THIS IS FIXED
				//WHY IS THE THE PLANE ALWAYS COLLDING WITH OBJECTS ????
				if (shapeA->getNumChildShapes() > 0) {			
					if (shapeA->getChildShape(0)->getShapeType() == STATIC_PLANE_PROXYTYPE)  {
						return collides; //RETURN COLLID OR DOSNt HAPPEN
					};			
				};

				if (shapeB->getNumChildShapes() > 0) {
					if (shapeB->getChildShape(0)->getShapeType() == STATIC_PLANE_PROXYTYPE)  {
						return collides;//RETURN COLLID OR DOSNT HAPPEN
					};			
				};	
		
				//RETURN CALLBACK

				//if (moaiBodyA) {
				//	moaiBodyA->HandleCollision ( 1, moaiBodyA,moaiBodyB );
				//};

				if (moaiBodyB) {
					moaiBodyB->HandleCollision ( 1, moaiBodyB,moaiBodyA );
				};

			} else {
				//printf("NOT A MOAI BODY \n");
				//return collides;
			};

	




//*******************************
//COLLISION IS  A PLANE 

			//	if (shapeA->getNumChildShapes() > 0) {			
			//		if (shapeA->getChildShape(0)->getShapeType() == STATIC_PLANE_PROXYTYPE)  {
			//			return collides; //RETURN COLLID OR DOSNt HAPPEN
			//		};			
			//	};

			//	if (shapeB->getNumChildShapes() > 0) {
			//		if (shapeB->getChildShape(0)->getShapeType() == STATIC_PLANE_PROXYTYPE)  {
			//			return collides;//RETURN COLLID OR DOSNT HAPPEN
			//		};			
			//	};	




			//
			//////PUSH TO CALLBACK
			//btRigidBody* rigBodyA = ( btRigidBody* )colObj0;
			//MOAIBulletBody* moaiBodyA = ( MOAIBulletBody* )rigBodyA->getUserPointer (); 			
			//
			//btRigidBody* rigBodyB = ( btRigidBody* )colObj1;
			//MOAIBulletBody* moaiBodyB = ( MOAIBulletBody* )rigBodyB->getUserPointer (); 			

			//	//if (moaiBodyA) {
			//	//	moaiBodyA->HandleCollision ( 1, moaiBodyA,moaiBodyB );
			//	//};

			//	if (moaiBodyB) {
			//		moaiBodyB->HandleCollision ( 1, moaiBodyB,moaiBodyA );
			//	};







		return collides;
	}
};
//----------------------------------------------------------------//
void MOAIBulletWorld::mNearCallback(btBroadphasePair& collisionPair, btCollisionDispatcher& dispatcher, const btDispatcherInfo& dispatchInfo) {
	btCollisionObject* colObj0 = static_cast<btCollisionObject*>(collisionPair.m_pProxy0->m_clientObject);
	btCollisionObject* colObj1 = static_cast<btCollisionObject*>(collisionPair.m_pProxy1->m_clientObject);

	if(dispatcher.needsCollision(colObj0,colObj1))
	{
		btCollisionObjectWrapper obj0Wrap(0,colObj0->getCollisionShape(),colObj0,colObj0->getWorldTransform(),-1,-1);
		btCollisionObjectWrapper obj1Wrap(0,colObj1->getCollisionShape(),colObj1,colObj1->getWorldTransform(),-1,-1);	
		
		//dispatcher will keep algorithms persistent in the collision pair
		if (!collisionPair.m_algorithm)
		{
			collisionPair.m_algorithm = dispatcher.findAlgorithm(&obj0Wrap,&obj1Wrap);
		}
		if (collisionPair.m_algorithm)
		{
			btManifoldResult contactPointResult(&obj0Wrap,&obj1Wrap);


			if (dispatchInfo.m_dispatchFunc == btDispatcherInfo::DISPATCH_DISCRETE)
			{
				//discrete collision detection query
				collisionPair.m_algorithm->processCollision(&obj0Wrap,&obj1Wrap,dispatchInfo,&contactPointResult);

				//CALL TO LUA
				btRigidBody* rigBodyA = ( btRigidBody* )colObj0;
				MOAIBulletBody* moaiBodyA = ( MOAIBulletBody* )rigBodyA->getUserPointer (); 
			
				//
				btRigidBody* rigBodyB = ( btRigidBody* )colObj1;
				MOAIBulletBody* moaiBodyB = ( MOAIBulletBody* )rigBodyB->getUserPointer (); 			

				moaiBodyB->HandleCollision ( 1, moaiBodyA,moaiBodyB );			}
			else
			{
				//continuous collision detection query, time of impact (toi)
				btScalar toi = collisionPair.m_algorithm->calculateTimeOfImpact(colObj0,colObj1,dispatchInfo,&contactPointResult);
				if (dispatchInfo.m_timeOfImpact > toi)
				{
					dispatchInfo.m_timeOfImpact = toi;
				}
			}
			if (contactPointResult.getPersistentManifold()->getNumContacts()>0) 
			{			


			
			}
		}
	}
	dispatcher.defaultNearCallback(collisionPair, dispatcher, dispatchInfo);

}



//----------------------------------------------------------------//
//----------------------------------------------------------------//
//----------------------------------------------------------------//
void MOAIBulletWorld::OnUpdate ( float step ) {			
     mWorld->stepSimulation( mStep, mMaxSubSteps);	
//UPDATE ALL OBJECTS
	for (int j=mWorld->getNumCollisionObjects()-1; j>=0 ;j--){	
		btCollisionObject* obj = mWorld->getCollisionObjectArray()[j];
		btRigidBody* body = btRigidBody::upcast(obj);

		//ACTIVE AND AWAKE THE SAME THING?
			if ( body->isActive()) {
				if (body && body->getMotionState())
				{								
						//FIX FOR RAG DOLLS
						MOAIBulletBody* moaiBody = ( MOAIBulletBody* )body->getUserPointer (); //HAD TO ADD TO BULLET
						if (moaiBody) {
							moaiBody->ScheduleUpdate ();
						}
				};
			
			};	
	}


//***************************************************************************************************
//***************************************************************************************************
//***************************************************************************************************
//COLLISION MANIFOLDS
 /*  int numManifolds = mWorld->getDispatcher()->getNumManifolds();
    for (int i=0;i<numManifolds;i++)
    {
        btPersistentManifold* contactManifold =  mWorld->getDispatcher()->getManifoldByIndexInternal(i);
        btCollisionObject* obA =  const_cast<btCollisionObject*>(contactManifold->getBody0());
        btCollisionObject* obB =  const_cast<btCollisionObject*>(contactManifold->getBody1());

        int numContacts = contactManifold->getNumContacts();
        for (int j=0;j<numContacts;j++)
        {
            btManifoldPoint& pt = contactManifold->getContactPoint(j);
            if (pt.getDistance()<0.f)
            {
				printf("objects \n");
		CALL TO LUA
				btRigidBody* rigBodyA = ( btRigidBody* )obA;
				btRigidBody* rigBodyB = ( btRigidBody* )obB;

				MOAIBulletBody* moaiBodyA = ( MOAIBulletBody* )rigBodyA->getUserPointer (); 				
				MOAIBulletBody* moaiBodyB = ( MOAIBulletBody* )rigBodyB->getUserPointer (); 			

				WHY IS I ON B
				moaiBodyB->HandleCollision ( 1, moaiBodyA,moaiBodyB );

				printf("COLLISION\n");
                const btVector3& ptA = pt.getPositionWorldOnA();
                const btVector3& ptB = pt.getPositionWorldOnB();
                const btVector3& normalOnB = pt.m_normalWorldOnB;

            }
        }
    }*/
//***************************************************************************************************
//***************************************************************************************************
//***************************************************************************************************
};
//----------------------------------------------------------------//
void MOAIBulletWorld::DrawDebug () {	
	if ( this->mDebugDraw ) {	

		MOAIDraw::Bind ();	
		this->mDebugDraw->mSize = 0;

		MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get ();	
		gfxDevice.SetVertexMtxMode ( MOAIGfxDevice::VTX_STAGE_MODEL, MOAIGfxDevice::VTX_STAGE_PROJ );
		gfxDevice.SetVertexTransform ( MOAIGfxDevice::VTX_WORLD_TRANSFORM );	
		gfxDevice.BeginPrim ( ZGL_PRIM_LINES );
				this->mDebugDraw->mScale = this->mDrawScale; 
				this->mWorld->debugDrawWorld();

		gfxDevice.setPrimeSize(this->mDebugDraw->mSize*2);
		gfxDevice.EndPrim ();
	}
}






//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************

//----------------------------------------------------------------//
void MOAIBulletWorld::SayGoodbye ( btCompoundShape* shape) {

		MOAIBulletShape* moaishape = ( MOAIBulletShape* )shape->getUserPointer();
		if ( moaishape->mShape ) {
			moaishape->mShape = 0;
			moaishape->SetWorld ( 0 );
			this->LuaRelease ( moaishape );
		}
}

//----------------------------------------------------------------//
void MOAIBulletWorld::SayGoodbye ( btTypedConstraint* joint ) {


	MOAIBulletJoint* moaiJoint = ( MOAIBulletJoint* )joint->getUserConstraintPtr();
	if ( moaiJoint->mJoint ) {
			moaiJoint->mJoint = 0;
			moaiJoint->SetWorld ( 0 );
			this->LuaRelease ( moaiJoint );
	}

}
//----------------------------------------------------------------//
void MOAIBulletWorld::ScheduleDestruction (MOAIBulletBody& body) {

	if ( !body.mDestroy ) {
		body.mDestroyNext = this->mDestroyBodies;
		this->mDestroyBodies = &body;
		body.mDestroy = true;
	}
	this->Destroy ();
}
//----------------------------------------------------------------//
void MOAIBulletWorld::ScheduleDestruction ( MOAIBulletShape& shape ) {

	if ( !shape.mDestroy ) {
		shape.mDestroyNext = this->mDestroyShapes;
		this->mDestroyShapes = &shape;
		shape.mDestroy = true;
	}
	this->Destroy ();
}
//----------------------------------------------------------------//
void MOAIBulletWorld::ScheduleDestruction (  MOAIBulletJoint& joint ) {

	if ( !joint.mDestroy ) {
		joint.mDestroyNext = this->mDestroyJoints;
		this->mDestroyJoints = &joint;
		joint.mDestroy = true;
	}
	this->Destroy ();
}
//----------------------------------------------------------------//
//I DON'T UNDERSTAND HOW THIS WORKS ???
//THIS IS CALLED FROM THE SECHDUAL DES

void MOAIBulletWorld::Destroy () {
	printf("\nMOAIBulletWorld::Destroy\n");

	if ( this->mLock ) return;
	this->mLock = true;

	while ( this->mDestroyShapes ) {
		MOAIBulletPrim* prim = this->mDestroyShapes;
		this->mDestroyShapes = this->mDestroyShapes->mDestroyNext;
		prim->Destroy ();		
		prim->SetWorld ( 0 );
		this->LuaRelease ( prim );
	}
	
	while ( this->mDestroyJoints ) {
		MOAIBulletPrim* prim = this->mDestroyJoints;
		this->mDestroyJoints = this->mDestroyJoints->mDestroyNext;
		prim->Destroy ();
		
		prim->SetWorld ( 0 );
		this->LuaRelease ( prim );
	}
	
	while ( this->mDestroyBodies ) {
		MOAIBulletPrim* prim = this->mDestroyBodies;
		this->mDestroyBodies = this->mDestroyBodies->mDestroyNext;
		prim->Destroy ();		
		prim->SetWorld ( 0 );
		this->LuaRelease ( prim );
	}	
	this->mLock = false;
}




//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//***************************************************************************
//CREATE



//----------------------------------------------------------------//
int MOAIBulletWorld::_create( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )

	self->mBroadphase				= new btDbvtBroadphase();	
	self->mCollisionConfiguration	= new btDefaultCollisionConfiguration(self->mConstructionInfo);
	self->mCollisionDispatcher		= new btCollisionDispatcher(self->mCollisionConfiguration);
	self->mSolver					= new btSequentialImpulseConstraintSolver;
	self->mWorld					= new btDiscreteDynamicsWorld(self->mCollisionDispatcher, self->mBroadphase, self->mSolver, self->mCollisionConfiguration);

	//*********************************************************
	//SWEEPING ???
		//const btVector3 worldAabbMin( -1000.0, -1000.0, -1000.0 );
		//const btVector3 worldAabbMax( 1000.0, 1000.0, 1000.0 );
		//btBroadphaseInterface = new btAxisSweep3(worldAabbMin, worldAabbMax, 1638 );

	//GRAVITY
		self->mWorld->setGravity(btVector3(0, 0, 0));
	
	//SOLVER
		self->mWorld->getSolverInfo().m_splitImpulse			= false; // Disable by default for performance

	//DISPATCH
		self->mWorld->getDispatchInfo().m_useContinuous			= false;
		self->mWorld->getDispatchInfo().m_enableSPU				= false;
		self->mWorld->getDispatchInfo().m_allowedCcdPenetration = 0.01f;


	//OTHER STUFF ???????
			//self->mWorld->setNumTasks

	self->mDebugDraw = new MOAIBulletDebugDraw ();
	self->mWorld->setDebugDrawer(self->mDebugDraw );		

	//****************************************************
	//****************************************************
	//****************************************************
			//SET CALLBACKS : DOSEN"T WORK
				//ICollisionEvents::SetInstance(this,this->mWorld);
				//gContactAddedCallback//=callbackFunc;

			//NEAR
	//****************************************************
	//****************************************************
	//****************************************************


			//mCollisionDispatcher->setNearCallback(this->mNearCallback);

			//CURRENT
				btOverlapFilterCallback * filterCallback = new YourOwnFilterCallback();
				self->mWorld->getPairCache()->setOverlapFilterCallback(filterCallback);

	return 1;
}

//----------------------------------------------------------------//
MOAIBulletWorld::MOAIBulletWorld () :
    mCollisionConfiguration(0),
    mCollisionDispatcher(0),
	mDebugDraw(0),
    mBroadphase(0),
    mSolver(0),
    mWorld(0),
	mDrawScale(1),
	mDrawJointSize(1),
	mStep(1/60),
	mMaxSubSteps(10),
	mLock(false)

{

RTTI_BEGIN
	RTTI_EXTEND ( MOAIAction )			
RTTI_END
//PRO-is wrapped in 

	//LOWER MEMORY FOOT PRINT ?????
	 this->mConstructionInfo		=  btDefaultCollisionConstructionInfo();
				//mConstructionInfo.m_defaultMaxCollisionAlgorithmPoolSize = 1023;
				//mConstructionInfo.m_defaultMaxPersistentManifoldPoolSize = 1023;	
				//m_defaultMaxPersistentManifoldPoolSize( 1638 ), //65536
				//m_defaultMaxCollisionAlgorithmPoolSize( 1638 ), //65536
				//m_defaultStackAllocatorSize( 131072 ) // 5 * 1024 * 1024
};
//----------------------------------------------------------------//
MOAIBulletWorld::~MOAIBulletWorld () {
	printf("\nMOAIBulletWorld::~MOAIBulletWorld\n");

	//THIS IS BODY NEEDS TO GET ALL SHAPES TO DELETE
	if (this->mWorld) {
			int i;

			for (i=this->mWorld->getNumCollisionObjects()-1; i>=0 ;i--)
			{
				//btCollisionObject* obj = this->mWorld->getCollisionObjectArray()[i];
				//btRigidBody* body = btRigidBody::upcast(obj);
				//if (body && body->getMotionState())
				//{
				//	delete body->getMotionState();
				//}
				//this->mWorld->removeCollisionObject( obj );
				//delete obj;
			}
	};


	if (this->mWorld) {
		delete mWorld;
	};

	if (this->mSolver) {
		delete mSolver;
	}

	if (this->mCollisionDispatcher) {
		delete mCollisionDispatcher;
	}

	if (this->mCollisionConfiguration) {
		delete mCollisionConfiguration;
	}

	if (this->mBroadphase) {
		delete mBroadphase;
	}

	if (this->mDebugDraw) {
		delete mDebugDraw;
	}

	//this->Destroy ();
};
//----------------------------------------------------------------//
int MOAIBulletWorld::_newBody ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UU" )	

	MOAIBulletTransform* transA = state.GetLuaObject < MOAIBulletTransform >(2, true );
	if ( !( transA )) return 0;
	btTransform ta = *transA->mTransform;

	//RESET VALUES	

	//NEW CLASS
		MOAIBulletBody* body = new MOAIBulletBody ();	
	//MASS
		btScalar mMass = 1.0;
	//INERTIA
		btVector3 mInertia(0.0, 0.0, 0.0);
	//MOTION & COMPOIND
		body->mMotion	= new btDefaultMotionState(ta);	
		body->mCompound = new btCompoundShape();   	

//printf("TRACE 1. btDefaultMotionState \n");
//printf("TRACE 2. btCompoundShape \n");
//printf("TRACE 3. btRigidBodyConstructionInfo \n");

	btRigidBody::btRigidBodyConstructionInfo info(mMass,body->mMotion,body->mCompound,mInertia);  
	
	//*********************************************************
	//*********************************************************
	//*********************************************************
	//*********************************************************
			//body->mBody = new btRigidBody(info); //DOESN'T WORK
			//static_cast <btRigidBodyWithEvents*> (body->mBody)->setMonitorCollisions(true); 
			//static_cast <btRigidBodyWithEvents*>(body->mBody)->setMonitorCollisions(true);
			//body->mBody->setMonitorCollisions(true);	

	//*********************************************************
	//*********************************************************
	//*********************************************************
	//*********************************************************
	
	body->mBody = new btRigidBody(info);

	body->setWorld(self->mWorld);	
	body->SetBody(body->mBody);
	self->LuaRetain ( body );
	body->PushLuaUserdata ( state );
	return 1;
}




//----------------------------------------------------------------//
int MOAIBulletWorld::_addJointHinge ( lua_State* L ) {	
//DISSABLE COLLISION BETWEEN BODIES --> self->mWorld->addConstraint(btJoint, false);
//USE FRAME A						--> btHingeConstraint(*bodyA->mBody, *bodyB->mBody, ta, tb);


	MOAI_LUA_SETUP ( MOAIBulletWorld, "UUUUUB" )	


	MOAIBulletBody* bodyA = state.GetLuaObject < MOAIBulletBody >( 2, true );
	MOAIBulletBody* bodyB = state.GetLuaObject < MOAIBulletBody >( 3, true );
	
	if ( !( bodyA && bodyB )) return 0;


		MOAIBulletTransform* transA = state.GetLuaObject < MOAIBulletTransform >( 4, true );
		MOAIBulletTransform* transB = state.GetLuaObject < MOAIBulletTransform >( 5, true );

		if ( !( transA && transB )) return 0;

			bool joint_bool = state.GetValue < bool >( 6, false );

			btTransform ta = *transA->mTransform;
			btTransform tb = *transB->mTransform;

			btHingeConstraint* btJoint = new btHingeConstraint(*bodyA->mBody, *bodyB->mBody, ta, tb,joint_bool);
			btJoint->setDbgDrawSize(self->mDrawJointSize);	

			MOAIBulletJointHinge* mJoint = new MOAIBulletJointHinge (); 

			mJoint->SetJoint(btJoint); 	 // HERE SETS --> btJoint->setUserConstraintPtr(mJoint); 


			mJoint->SetBodyA(bodyA);
			mJoint->SetBodyB(bodyB);
			mJoint->SetWorld ( self->mWorld );

			mJoint->LuaRetain ( bodyA );
			mJoint->LuaRetain ( bodyB );

			self->LuaRetain ( mJoint );
			mJoint->PushLuaUserdata ( state );

	return 1;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_addJointCone ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UUUUUB" )	
	
	MOAIBulletBody* bodyA = state.GetLuaObject < MOAIBulletBody >( 2, true );
	MOAIBulletBody* bodyB = state.GetLuaObject < MOAIBulletBody >( 3, true );

		if ( !( bodyA && bodyB )) return 0;

		MOAIBulletTransform* transA = state.GetLuaObject < MOAIBulletTransform >( 4, true );
		MOAIBulletTransform* transB = state.GetLuaObject < MOAIBulletTransform >( 5, true );

			if ( !( transA && transB )) return 0;

				//NOT USED
				bool joint_bool = state.GetValue < bool >( 6, false );

				btTransform ta = *transA->mTransform;
				btTransform tb = *transB->mTransform;

				btConeTwistConstraint* btJoint = new btConeTwistConstraint(*bodyA->mBody, *bodyB->mBody, ta, tb);
				btJoint->setDbgDrawSize(self->mDrawJointSize);

				MOAIBulletJointCone* mJoint = new MOAIBulletJointCone ();
				mJoint->SetJoint(btJoint);  // HERE SETS --> btJoint->setUserConstraintPtr(mJoint); 

				mJoint->SetBodyA(bodyA);
				mJoint->SetBodyB(bodyB);
				mJoint->SetWorld ( self->mWorld );

				mJoint->LuaRetain ( bodyA );
				mJoint->LuaRetain ( bodyB );
			

				self->LuaRetain ( mJoint );
				mJoint->PushLuaUserdata ( state );


	return 1;
};
//----------------------------------------------------------------//
int MOAIBulletWorld::_addJointSlider ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UUUUUB" )	

	MOAIBulletBody* bodyA = state.GetLuaObject < MOAIBulletBody >( 2, true );
	MOAIBulletBody* bodyB = state.GetLuaObject < MOAIBulletBody >( 3, true );
	
	if ( !( bodyA && bodyB )) return 0;

		MOAIBulletTransform* transA = state.GetLuaObject < MOAIBulletTransform >( 4, true );
		MOAIBulletTransform* transB = state.GetLuaObject < MOAIBulletTransform >( 5, true );

		if ( !( transA && transB )) return 0;

			btTransform ta = *transA->mTransform;
			btTransform tb = *transB->mTransform;

			bool joint_bool = state.GetValue < bool >( 6, false );

			btSliderConstraint*	 btJoint = new btSliderConstraint(*bodyA->mBody, *bodyB->mBody, ta, tb,joint_bool); 
			btJoint->setDbgDrawSize(self->mDrawJointSize);

			MOAIBulletJointSlide* mJoint = new MOAIBulletJointSlide (); 
			mJoint->SetJoint(btJoint); // HERE SETS --> btJoint->setUserConstraintPtr(mJoint); 

			mJoint->SetBodyA(bodyA);
			mJoint->SetBodyB(bodyB);
			mJoint->SetWorld ( self->mWorld );

			mJoint->LuaRetain ( bodyA );
			mJoint->LuaRetain ( bodyB );	

			self->LuaRetain ( mJoint );
			mJoint->PushLuaUserdata ( state );



//*******************************************************************
//*******************************************************************

		//sliderC->setBreakingImpulseThreshold(100.0f);
		//sliderC->setLowerLinLimit(-15.0F);
		//sliderC->setUpperLinLimit(-5.0F);
		//sliderC->setLowerAngLimit(-SIMD_PI / 3.0F);
		//sliderC->setUpperAngLimit( SIMD_PI / 3.0F);
		//self->mWorld->addConstraint(sliderC, true);

//*******************************************************************
//*******************************************************************




	
	return 1;
};
//----------------------------------------------------------------//
int MOAIBulletWorld::_addJointFreedom ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UUUUUB" )	


	MOAIBulletBody* bodyA = state.GetLuaObject < MOAIBulletBody >( 2, true );
	MOAIBulletBody* bodyB = state.GetLuaObject < MOAIBulletBody >( 3, true );
	
	if ( !( bodyA && bodyB )) return 0;

		MOAIBulletTransform* transA = state.GetLuaObject < MOAIBulletTransform >( 4, true );
		MOAIBulletTransform* transB = state.GetLuaObject < MOAIBulletTransform >( 5, true );

		if ( !( transA && transB )) return 0;

			bool joint_bool = state.GetValue < bool >( 6, false );

			btTransform ta = *transA->mTransform;
			btTransform tb = *transB->mTransform;		
	
			btGeneric6DofConstraint* btJoint = new btGeneric6DofConstraint(*bodyA->mBody, *bodyB->mBody, ta, tb,joint_bool); //ANOTHER ARGGUMENT
			btJoint->setDbgDrawSize(self->mDrawJointSize);

			MOAIBulletJointFreedom* mJoint = new MOAIBulletJointFreedom (); 

			mJoint->SetJoint(btJoint);  // HERE SETS --> btJoint->setUserConstraintPtr(mJoint); 

			mJoint->SetBodyA(bodyA);
			mJoint->SetBodyB(bodyB);

			mJoint->SetWorld ( self->mWorld );
			mJoint->LuaRetain ( bodyA );
			mJoint->LuaRetain ( bodyB );

			self->LuaRetain ( mJoint );
			mJoint->PushLuaUserdata ( state );



//*******************************************************************
//*******************************************************************
	btJoint->setBreakingImpulseThreshold(100.0f);
	btTransform sliderTransform;
	btVector3 lowerSliderLimit = btVector3(-10,0,0);
	btVector3 hiSliderLimit = btVector3(10,0,0);

	btJoint->setLinearLowerLimit(lowerSliderLimit);
	btJoint->setLinearUpperLimit(hiSliderLimit);
	btJoint->setAngularLowerLimit(btVector3(-SIMD_PI,0,0));
	btJoint->setAngularUpperLimit(btVector3(1.5,0,0));

	btJoint->getTranslationalLimitMotor()->m_enableMotor[0] = true;
	btJoint->getTranslationalLimitMotor()->m_targetVelocity[0] = -5.0f;
	btJoint->getTranslationalLimitMotor()->m_maxMotorForce[0] = 0.1f;

//*******************************************************************
//*******************************************************************



//***********************************************************************
//***********************************************************************

//btGeneric6DofSpringConstraint* pGen6DOFSpring = new btGeneric6DofSpringConstraint(*pBodyA, *pBodyB, frameInA, frameInB, true);
//pGen6DOFSpring->setLinearUpperLimit(btVector3(5., 0., 0.));
//pGen6DOFSpring->setLinearLowerLimit(btVector3(-5., 0., 0.));
//pGen6DOFSpring->setAngularLowerLimit(btVector3(0.f, 0.f, -1.5f));
//pGen6DOFSpring->setAngularUpperLimit(btVector3(0.f, 0.f, 1.5f));
//m_dynamicsWorld->addConstraint(pGen6DOFSpring, true);
//pGen6DOFSpring->setDbgDrawSize(btScalar(5.f));
//pGen6DOFSpring->enableSpring(0, true);
//pGen6DOFSpring->setStiffness(0, 39.478f);
//pGen6DOFSpring->setDamping(0, 0.5f);
//pGen6DOFSpring->enableSpring(5, true);
//pGen6DOFSpring->setStiffness(5, 39.478f);
//pGen6DOFSpring->setDamping(0, 0.3f);
//pGen6DOFSpring->setEquilibriumPoint();


	return 1;
};
//----------------------------------------------------------------//
int MOAIBulletWorld::_addJointFixed ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UUUUU" )	
		

	MOAIBulletBody* bodyA = state.GetLuaObject < MOAIBulletBody >( 2, true );
	MOAIBulletBody* bodyB = state.GetLuaObject < MOAIBulletBody >( 3, true );
		
	if ( !( bodyA && bodyB )) return 0;

		MOAIBulletTransform* transA = state.GetLuaObject < MOAIBulletTransform >( 4, true );
		MOAIBulletTransform* transB = state.GetLuaObject < MOAIBulletTransform >( 5, true );

		if ( !( transA && transB )) return 0;

			//NOT USED
			bool joint_bool = state.GetValue < bool >( 6, false );

			btTransform ta = *transA->mTransform;
			btTransform tb = *transB->mTransform;
	
			btFixedConstraint* btJoint = new btFixedConstraint(*bodyA->mBody, *bodyB->mBody, ta, tb); 
			btJoint->setDbgDrawSize(self->mDrawJointSize);

			MOAIBulletJointFixed* mJoint = new MOAIBulletJointFixed (); 

			mJoint->SetJoint(btJoint);  // HERE SETS --> btJoint->setUserConstraintPtr(mJoint); 

			mJoint->SetBodyA(bodyA);
			mJoint->SetBodyB(bodyB);
			mJoint->SetWorld ( self->mWorld );

			mJoint->LuaRetain ( bodyA );
			mJoint->LuaRetain ( bodyB );

			self->LuaRetain ( mJoint );
			mJoint->PushLuaUserdata ( state );

	return 1;
};
//----------------------------------------------------------------//
int MOAIBulletWorld::_addJointPoint ( lua_State* L ) {
//PIGGY BACK OFF TRANSFORM ??
//REQURES VEC3?

	
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UUUUUB" )

	MOAIBulletBody* bodyA = state.GetLuaObject < MOAIBulletBody >( 2, true );
	MOAIBulletBody* bodyB = state.GetLuaObject < MOAIBulletBody >( 3, true );
	
	if ( !( bodyA && bodyB )) return 0;

	//float a_x = state.GetValue < float >( 4, 0.0f );
	//float a_y = state.GetValue < float >( 5, 0.0f );
	//float a_z = state.GetValue < float >( 6, 0.0f );

	//float b_x = state.GetValue < float >( 7, 0.0f );
	//float b_y = state.GetValue < float >( 8, 0.0f );
	//float b_z = state.GetValue < float >( 9, 0.0f );
	//if ( !( bodyA && bodyB )) return 0;

		MOAIBulletTransform* transA = state.GetLuaObject < MOAIBulletTransform >( 4, true );
		MOAIBulletTransform* transB = state.GetLuaObject < MOAIBulletTransform >( 5, true );

		if ( !( transA && transB )) return 0;

		btTransform* mTransformA = ( btTransform* )transA->mTransform;
		btTransform* mTransformB = ( btTransform* )transB->mTransform;

		btVector3 pivotInA = mTransformA->getOrigin();
		btVector3 pivotInB = mTransformB->getOrigin();

		//printf("%f %f %f \n",mTransformA->getOrigin().x(),mTransformA->getOrigin().y(),mTransformA->getOrigin().z());
		//printf("%f %f %f \n",mTransformA->getOrigin().x(),mTransformA->getOrigin().getY(),mTransformA->getOrigin().getZ());
		

	btPoint2PointConstraint*	btJoint = new btPoint2PointConstraint(*bodyA->mBody, *bodyB->mBody, pivotInA, pivotInB); 
	btJoint->setDbgDrawSize(self->mDrawJointSize);

	MOAIBulletJointPoint* mJoint = new MOAIBulletJointPoint (); 

	mJoint->SetJoint(btJoint); 	 // HERE SETS --> btJoint->setUserConstraintPtr(mJoint); 

	mJoint->SetBodyA(bodyA);
	mJoint->SetBodyB(bodyB);
	mJoint->SetWorld ( self->mWorld );

	mJoint->LuaRetain ( bodyA );
	mJoint->LuaRetain ( bodyB );

	self->LuaRetain ( mJoint );
	mJoint->PushLuaUserdata ( state );

	return 1;
};
//----------------------------------------------------------------//
int MOAIBulletWorld::_setStep ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UN" )
	float step = state.GetValue < float >( 2, 1.0f/60.0f );
	self->mStep = step;	
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_setMaxSubSteps ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UN" )
	int step = state.GetValue < int >( 2, 10 );
	self->mMaxSubSteps = step;	
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_setGravity ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UN" )	
	float gravity_x = state.GetValue < float >( 2, 0.0f );
	float gravity_y = state.GetValue < float >( 3, 0.0f );
	float gravity_z = state.GetValue < float >( 4, 0.0f );
	self->mWorld->setGravity(btVector3(gravity_x, gravity_y, gravity_z));
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletWorld::_setForceUpdateAllAabbs ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )
	bool forceUpdate = state.GetValue < bool >( 2, true );
	self->mWorld->setForceUpdateAllAabbs(forceUpdate);
	return 1;
};
//----------------------------------------------------------------//
int MOAIBulletWorld::_defaultMaxCollisionAlgorithmPoolSize ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UN" )
	int defaultMaxCollisionAlgorithmPoolSize = state.GetValue < int >( 2, 0 );
	self->mConstructionInfo.m_defaultMaxCollisionAlgorithmPoolSize = defaultMaxCollisionAlgorithmPoolSize;
	return 0;	
};
//----------------------------------------------------------------//
int MOAIBulletWorld::_defaultMaxPersistentManifoldPoolSize ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )
	int defaultMaxCollisionAlgorithmPoolSize = state.GetValue < int >( 2, 0 );
	self->mConstructionInfo.m_defaultMaxPersistentManifoldPoolSize = defaultMaxCollisionAlgorithmPoolSize;
	return 0;
};
//----------------------------------------------------------------//
int MOAIBulletWorld::_useContinuous ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )
	bool continous = state.GetValue < bool >( 2, true );
	self->mWorld->getDispatchInfo().m_useContinuous	= continous;
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_enableSPU	( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )
	bool spu = state.GetValue < bool >( 2, true );
	self->mWorld->getDispatchInfo().m_enableSPU	= spu;
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_allowedCcdPenetration	( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )
	float pen = state.GetValue < float >( 2, 0.0f );
	self->mWorld->getDispatchInfo().m_allowedCcdPenetration	= pen;
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_splitImpulse ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )
	bool impluse = state.GetValue < bool >( 2, true );
	///NOT SURE WHY EXMAPLE SHOWS BOOLEAN BECAUSE IT WANTS AN INTEGER
	self->mWorld->getSolverInfo().m_splitImpulse		= impluse;	
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_Iterations ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UN" )	
	int iterations = state.GetValue < int >( 2, 4 );
	btContactSolverInfo& info = self->mWorld->getSolverInfo();
	info.m_numIterations = iterations;
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_setDrawScale ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UN" )	
	float drawScale = state.GetValue < float >( 2, 1.0f );
	self->mDrawScale = drawScale;
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_setDrawJointSize ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "UN" )	
	float drawSize = state.GetValue < float >( 2, 1.0f );
	self->mDrawJointSize = drawSize;
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_DrawDebugLua ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )	
	self->DrawDebug();	
	return 0;
}
//----------------------------------------------------------------//
int MOAIBulletWorld::_forceStep ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )	
		self->OnUpdate(0);
		return 0;
};

//----------------------------------------------------------------//
int MOAIBulletWorld::_addCollisionObject ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )	
		//self->mWorld->addCollisionObject(); ///WHAT THE FUCK ???
		return 0;
};
//----------------------------------------------------------------//
int MOAIBulletWorld::_removeCollisionObject ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIBulletWorld, "U" )	
		//self->mWorld->removeCollisionObject(); ///WHAT THE FUCK ???
		return 0;
};
//----------------------------------------------------------------//





//----------------------------------------------------------------//
//----------------------------------------------------------------//
void MOAIBulletWorld::RegisterLuaClass ( MOAILuaState& state ) {
	MOAIAction::RegisterLuaClass ( state );		

	state.SetField ( -1, "ACTIVE_TAG",				( u32 )1 );
	state.SetField ( -1, "ISLAND_SLEEPING",			( u32 )2 );
	state.SetField ( -1, "WANTS_DEACTIVATION",		( u32 )3 );
	state.SetField ( -1, "DISABLE_DEACTIVATION",	( u32 )4 );
	state.SetField ( -1, "DISABLE_SIMULATION",		( u32 )5 );

//#define ACTIVE_TAG 1
//#define ISLAND_SLEEPING 2
//#define WANTS_DEACTIVATION 3
//#define DISABLE_DEACTIVATION 4
//#define DISABLE_SIMULATION 5

}

//----------------------------------------------------------------//
void MOAIBulletWorld::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAIAction::RegisterLuaFuncs ( state );
	luaL_Reg regTable [] = {

//*******************************************************
//*******************************************************
//TESTING
		{"testJoint",					 _testJoint},
		{"testRagDoll",					 _testRagDoll},
		{"testCar",						 _testCar},
		{"testCarUpdate",				 _testCarUpdate},
//*******************************************************
//*******************************************************






		{"forceStep",					 _forceStep},
	

//MANIFOLD
		{ "defaultMaxCollisionAlgorithmPoolSize",					_defaultMaxCollisionAlgorithmPoolSize }, 
		{ "defaultMaxPersistentManifoldPoolSize",					_defaultMaxPersistentManifoldPoolSize }, 
//INTI
		{ "create",						_create }, 
		{ "newBody",					_newBody }, 
//JOINTS
		{ "addJointHinge",				_addJointHinge },
		{ "addJointCone",				_addJointCone }, 
		{ "addJointFixed",				_addJointFixed },
		{ "addJointPoint",				_addJointPoint },
		{ "addJointSlider",				_addJointSlider },
		{ "addJointFreedom",			_addJointFreedom },

//WORLD
		{ "setDrawScale",				_setDrawScale },
		{ "setDrawJointSize",			_setDrawJointSize },
		{ "setForceUpdateAllAabbs",		_setForceUpdateAllAabbs },
		
		{ "setStep",					_setStep },
		{ "setMaxSubSteps",				_setMaxSubSteps },
	
		{ "setGravity",					_setGravity },
		{ "useContinuous",				_useContinuous },
		{ "splitImpulse",				_splitImpulse },

		{ "allowedCcdPenetration",		_allowedCcdPenetration },
		{ "enableSPU",					_enableSPU },

		{ "iterations",					_Iterations },	
//DEBUG DRAW
		{"drawDebugLua",				_DrawDebugLua	},


//COLLISION OBJECT
	{"_addCollisionObject",				_addCollisionObject	},
	{"_removeCollisionObject",			_removeCollisionObject	},







		{ NULL, NULL }
	};	
	luaL_register ( state, 0, regTable );
}




