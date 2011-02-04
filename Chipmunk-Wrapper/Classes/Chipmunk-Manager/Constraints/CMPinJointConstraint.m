//
//  CMPinJointConstraint.m
//  Chipmunk
//
//  Created by Ronald Mathies on 1/9/11.
//  Copyright 2011 Sodeso. All rights reserved.
//

#import "CMPinJointConstraint.h"

// --- Static variables ----------------------------------------------------------------------------

// --- Static inline methods -----------------------------------------------------------------------

// --- private interface ---------------------------------------------------------------------------

@interface CMPinJointConstraint ()

@end

// --- Class implementation ------------------------------------------------------------------------

@implementation CMPinJointConstraint

- (id) initBetweenBody:(CMBody*)cmBody andBody:(CMBody*)andCmBody anchor1:(cpVect)anchor1 anchor2:(cpVect)anchor2 {
	if (self = [super init]) {
		cpBody *body1 = [cmBody cpBody];
		cpBody *body2 = [andCmBody cpBody];
		
		mCpConstraint = cpPinJointNew(body1, body2, anchor1, anchor2);
		mCpConstraint->data =[[CMData createWithObject:self] retain];
	}
	return self;
}

- (void)setDistance:(float)distance {
	((cpPinJoint*)mCpConstraint)->dist = distance;
}

@end
