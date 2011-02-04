//
//  CMBody.h
//  Chipmunk
//
//  Created by Ronald Mathies on 12/27/10.
//  Copyright 2010 Sodeso. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CMCircleShape; 
@class CMRectShape;
@class CMPolyShape;
@class CMSegmentShape;

@class CMSimpleMotorConstraint;
@class CMPinJointConstraint;
@class CMDampedRotarySpringConstraint;
@class CMDampedSpringConstraint;
@class CMGearJointConstraint;
@class CMGrooveJointConstraint;
@class CMPivotJointConstraint;
@class CMRatchetJointConstraint;
@class CMRotaryLimitConstraint;
@class CMSlideJointConstraint;

// --- Types ---------------------------------------------------------------------------------------

// --- Interface ---------------------------------------------------------------------------------------

/**
 * The body is used to specify an object. A body consists of one or more shapes and joints that make up
  * the complete object.
 */
@interface CMBody : CMObject {

@private	
	cpBody *mCpBody;
	
	NSMutableArray *mShapes;
	NSMutableArray *mConstraints;
}

- (id)initStatic;

@property (nonatomic, readonly) cpBody *cpBody;

/**
 * Constructs a new CMBody object with the given mass and moment.
 *
 * @param mass Mass of the body.
 * @param moment Moment of inertia (MoI or sometimes just moment) of the body. 
 *               The moment is like the rotational mass of a body.
 */
- (id) initWithMass:(float)mass moment:(float)moment;

#pragma mark Properties

/**
 * Set the mass.
 * @param mass the mass of the body.
 */
- (void)setMass:(float)mass;

/**
 * Set the moment.
 *
 * @param moment of inertia (MoI or sometimes just moment) of the body. 
 *               The moment is like the rotational mass of a body.
 */
- (void)setMoment:(float)moment;

/**
 * Sets the velocity of the body.
 *
 * @param velocity Velocity of the body.
 */
- (void) setVelocity:(cpVect)velocity;

/**
 * Sets the force.
 *
 * Note: does not reset automatically as in some physics engines.
 *
 * @param force Current force being applied to the body.
 */
- (void) setForce:(cpVect)force;

/**
 * Sets the position.
 *
 * @param coordinate Position of the body.
 */
- (void) setPosition:(cpVect)coordinate;

/**
 * Sets the angle.
 *
 * NOTE: When using Sparrow you can use the SP_D2R function 
 * to convert from degrees to radians.
 *
 * @param angle the angle in radians.
 */
- (void) setAngle:(float)angle;

/**
 * Sets the angulair velocity.
 *
 * @param velocity the velocity.
 */
- (void) setAngularVelocity:(float)velocity;

/**
 * Sets the torque
 *
 * @param the torque
 */
- (void) setTorque:(float)torque;

#pragma mark -

#pragma mark Data

/**
 * Associates an object with this body, it is not used by Chipmunk but can be used
 * to create a binding between an Sparrow object and a cpBody.
 *
 * @param data an object to associate
 */
- (void)setData:(id)data;

/**
 * Returns the associated object with this body.
 *
 * @return the associated object with this body.
 */
- (id)getData;

#pragma mark -

#pragma mark Operations

/**
 * Apply an impulse to this body at a relative offset from the center of gravity. Both the impulse and the offset are in world coordinates. offset is relative to the position of the body, but not the rotation.
 *
 * @param impulse the impulse relative to the center of gravity.
 * @param offset the offset relative to the body.
 */
- (void) applyImpulse:(cpVect)impulse offset:(cpVect)offset;

/**
 * Apply (accumulate) the force on the body at a relative offset (important!) from the center of gravity. Both the force and offset are in world coordinates.
 *
 * @param force the force
 * @param offset the offset
 */
- (void) applyForce:(cpVect)force offset:(cpVect)offset;

/**
 * Zero both the forces and torques accumulated on body.
 */
- (void) resetForces;

/**
 * Force the body to sleep.
 */
- (void) sleep;

/**
 * Force the body to wake up from sleep.
 */
- (void) wakeUp;

/**
 * Adds this body to the space.
 */
- (void) addToSpace;

/**
 * Remove this body from the space.
 */
- (void) removeFromSpace;

#pragma mark -

#pragma mark Shapes

/**
 * Create a new Circle shape associated with this body.
 *
 * @param radius the radius of the circle.
 *
 * @return The circle shape.
 */
- (CMCircleShape*) addCircleWithRadius:(float)radius;

/**
 * Create a new Circle shape associated with this body.
 *
 * @param radius the radius of the circle.
 * @param offset the offset of the shape in relation to the body.
 *
 * @return The circle shape.
 */
- (CMCircleShape*) addCircleWithRadius:(float)radius offset:(cpVect)offset;

/**
 * Create a new Rectangulair shape associated with this body.
 *
 * @param width the width of the rectangle (full-width)
 * @param height the height of the rectangle (full-height)
 *
 * @return the rectangulair shape.
 */
- (CMRectShape*) addRectWithWidth:(float)width height:(float)height;

/**
 * Create a new Rectangulair shape associated with this body.
 *
 * @param width the width of the rectangle (full-width)
 * @param height the height of the rectangle (full-height)
 * @param offset the offset of the shape in relation to the body.
 *
 * @return the rectangulair shape.
 */
- (CMRectShape*) addRectWithWidth:(float)width height:(float)height offset:(cpVect)offset;

/**
 * Create a new Polygon shape associated with this body.
 *
 * @param numberOfVertices the number of points
 * @param vertices the vertices
 *
 * @return The polygon shape.
 */
- (CMPolyShape*) addPolyWithPoints:(int)numberOfVertices vertices:(cpVect)vertices, ...;

/**
 * Create a new Polygon shape associated with this body.
 *
 * @param numberOfVertices the number of points
 * @param offset the offset of the shape in relation to the body.
 * @param vertices the vertices
 *
 * @return The polygon shape.
 */
- (CMPolyShape*) addPolyWithPoints:(int)numberOfVertices offset:(cpVect)offset vertices:(cpVect)vertices, ...;

/**
 * Create a new Segment shape associated with this body.
 *
 * @param from The starting point of the segment.
 * @param to The ending point of the segment.
 * @param radius The radius of the segment.
 */
- (CMSegmentShape*) addSegmentFrom:(cpVect)from to:(cpVect)to radius:(float)radius;

/**
 * Removes the specified shape from the body and space.
 *
 * @param shape the shape to remove.
 */
- (void)removeShape:(CMShape*)shape;

#pragma mark -

#pragma mark Constraints

- (void)removeConstraint:(CMConstraint*)constraint;

/**
 * Creates a new motor constraint between this body and the given body.
 *
 * @param cmBody The body which will function as the second body of the constraint.
 * @param rate the rate (angle) how much it should rotate within a single frame.
 */
- (CMSimpleMotorConstraint*) addSimpleMotorConstraintWithBody:(CMBody*)cmBody rate:(float)rate;

/**
 * Constructs a new pin joint constraint.
 *
 * @param cmBody The body which will function as the second body of the constraint.
 * @param anchor1  The anchor point on the first body. 
 * @param anchor2 The anchor point on the second body. 
 */
- (CMPinJointConstraint*) addPinJointConstraintWithBody:(CMBody*)cmBody anchor1:(cpVect)anchor1 anchor2:(cpVect)anchor2;

/**
  * Constructs a new damped rotary constraint.
  *
  * @param cmBody The body which will function as the second body of the constraint.
  * @param restAngle The angular offset the spring attempts to keep between the two bodies. 
  * @param stiffness The young's modulus of the spring.  (http://en.wikipedia.org/wiki/Young%27s_modulus)
  * @param damping The amount of viscous damping to apply. 
  */
- (CMDampedRotarySpringConstraint*) addDampedRotaryConstraintWithBody:(CMBody*)cmBody restAngle:(float)restAngle stiffness:(float)stiffness damping:(float)damping;

/**
  * Constructs a new damped spring.
  *
  * @param cmBody The body which will function as the second body of the constraint.
  * @param anchor1 The anchor point on the first body. 
  * @param anchor2 The anchor point on the second body. 
  * @param restLength The length the spring wants to contract or expand to. 
  * @param stiffness The young's modulus of the spring.  (http://en.wikipedia.org/wiki/Young%27s_modulus)
  * @param damping The amount of viscous damping to apply. 
  */
- (CMDampedSpringConstraint*) addDampedSpringConstraintWithBody:(CMBody*)cmBody anchor1:(cpVect)anchor1 anchor2:(cpVect)anchor2 restLength:(float)restLength stiffness:(float)stiffness damping:(float)damping;

/**
  * Constructs a new gear joint constraint.
  *
  * @param cmBody The body which will function as the second body of the constraint.
  * @param phase The angular offset of the ratchet positions in radians. 
  * @param ratio The angle in radians of each ratchet position. Negative values cause the ratchet to operate in the opposite direction. 
  */
- (CMGearJointConstraint*) addGearJointConstraintWithBody:(CMBody*)cmBody phase:(float)phase ratio:(float)ratio;

/**
  * Constructs a new groove joint constraint.
  *
  * @param cmBody The body which will function as the second body of the constraint.
  * @param grooveA The start of the line segment on the first body. 
  * @param grooveB The end of the line segment on the second body. 
  * @param anchor1 The anchor point on the second body that is held to the line segment on the first. 
  */
- (CMGrooveJointConstraint*) addGrooveJointConstraintWithBody:(CMBody*)cmBody grooveA:(cpVect)grooveA grooveB:(cpVect)grooveB anchor1:(cpVect)anchor1;

/**
 * Constructs a new groove joint constraint.
 *
 * @param cmBody The body which will function as the second body of the constraint.
 * @param anchor1 The start of the line segment on the first body. 
 * @param anchor2 The end of the line segment on the second body.
 */
- (CMPivotJointConstraint*) addPivotJointConstraintWithBody:(CMBody*)cmBody anchor1:(cpVect)anchor1 anchor2:(cpVect)anchor2;

/**
  * Constructs a new pivot joing using two anchors.
  *
  * @param cmBody The body which will function as the second body of the constraint.
  * @param pivot The pivot coordinate in the world. 
  */
- (CMPivotJointConstraint*) addPivotJointConstraintWithBody:(CMBody*)cmBody pivot:(cpVect)pivot;

/**
  * Constructs a new pivot joint using a pivot.
  *
  * @param cmBody The body which will function as the second body of the constraint.
  * @param pivot The pivot point.
  */
- (CMRatchetJointConstraint*) addRatchetJointConstraintWithBody:(CMBody*)cmBody phase:(float)phase ratchet:(float)ratchet;

/**
  * Constructs a new rotary limit constraint.
  *
  * @param cmBody The body which will function as the second body of the constraint.
  * @param min The minimum angular delta of the joint in radians. 
  * @param max The maximum angular delta of the joint in radians. 
  */
- (CMRotaryLimitConstraint*) addRotaryLimitConstraintWithBody:(CMBody*)cmBody min:(float)min max:(float)max;

/**
 * Constructs a new Slide joing constraint.
 *
 * @param cmBody The body which will function as the second body of the constraint.
 * @param anchor1 The anchor point on the first body. 
 * @param anchor2 The anchor point on the second body. 
 * @param min The minimum allowed distance between anchor points. 
 * @param max The maximum allowed distance between anchor points. 
 */
- (CMSlideJointConstraint*) addSlideJointConstraintWithBody:(CMBody*)cmBody anchor1:(cpVect)anchor1 anchor2:(cpVect)anchor2 min:(float)min max:(float)max;

#pragma mark -

@end
