#include "../L2_hw//Triangle.h"

int main()
{
	std::cout << "(3.5, 0, 0)x(1.75, 3.5, 0): " << cross(Point3(3.5, 0, 0), Point3(1.75, 3.5, 0)) << std::endl;
	std::cout << "(3, -3, 1)x(4, 9, 3): " << cross(Point3(3, -3, 1), Point3(4, 9, 3)) << std::endl;

	std::cout << "Area of parallelogram of (3, -3, 1) and (4, 9, 3): " << cross(Point3(3, -3, 1), Point3(4, 9, 3)).Length() << std::endl;
	std::cout << "Area of parallelogram of (3, -3, 1) and (-12, 12, -4): " << cross(Point3(3, -3, 1), Point3(-12, 12, -4)).Length() << std::endl;

	Triangle t0 = Triangle(Point3(-1.75, -1.75, -3), Point3(1.75, -1.75, -3), Point3(0, 1.75, -3), Color(0,0,0));
	Triangle t1 = Triangle(Point3(0, 0, -1), Point3(1, 0, 1), Point3(-1, 0, 1), Color(0,0,0));
	Triangle t2 = Triangle(Point3(0.56, 1.11, 1.23), Point3(0.44, -2.368, -0.54), Point3(-1.56, 0.15, -1.92), Color(0,0,0));

	std::cout << "T0 normal: " << t0.Normal() << " T0 area: " << t0.Area() << std::endl;
	std::cout << "T1 normal: " << t1.Normal() << " T1 area: " << t1.Area() << std::endl;
	std::cout << "T2 normal: " << t2.Normal() << " T2 area: " << t2.Area() << std::endl;

	std::cout << "Done" << std::endl;
	std::cin.get();
}