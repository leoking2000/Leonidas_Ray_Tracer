#pragma once
#pragma once
#include "../pch.h"

#include "../examples/ProjectileTest.h"
#include "../examples/clockpositionsTest.h"
#include "../examples/DrawSphereTest.h"

TEST(examples, Projectile)
{
	ProjectileTest();
}

TEST(examples, clockpositions)
{
	clockpositionsTest();
}

TEST(examples, DrawSphere)
{
	DrawSphereTest();
}