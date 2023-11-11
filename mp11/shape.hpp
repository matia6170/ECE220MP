/*
ECE 220 MP11

partners: hyunwoo6, crjung2, awinick2

This program is a shape calculator that reads shapes from a file and calculates the max area and volume.
Rectangle, Circle, Sphere, and RectPrism are the shapes that can be read from the file.
*/
#ifndef SHAPE_H_
#define SHAPE_H_

#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<list>
#include<fstream>
#include <iomanip>    

using namespace std;

//Base class
//Please implement Shape's member functions
//constructor, getName()
class Shape {
public:
	//Base class' constructor should be called in derived classes'
	//constructor to initizlize Shape's private variable 

	Shape(string name) {
		name_ = name;
	}

	string getName() {
		return name_;
	}

	virtual double getArea() const = 0;
	virtual double getVolume() const = 0;

private:
	string name_;


};

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-

template <class T>
class Rectangle : public Shape {
public:
	// constructor for Rectangle with name "Rectangle" and default value 0 for width and length
	Rectangle<T>(T width = 0, T length = 0) :Shape("Rectangle") {
		width_ = width;
		length_ = length;
	}

	// return area of Rectangle
	double getArea() const {
		return width_ * length_;
	}

	// return volume of Rectangle
	double getVolume() const {
		return 0;

	}

	// overload operator + to add two Rectangles
	Rectangle<T> operator + (const Rectangle<T>& rec) {
		return Rectangle<T>(width_ + rec.getWidth(), length_ + rec.getLength());

	}

	// overload operator - to subtract two Rectangles
	Rectangle<T> operator - (const Rectangle<T>& rec) {
		// if the result is negative for each dimension, return 0 for each
		return Rectangle<T>(
			(width_ - rec.getWidth() > 0 ? width_ - rec.getWidth() : 0),
			(length_ - rec.getLength() > 0 ? length_ - rec.getLength() : 0)
		);
	}

	// return width of Rectangle
	T getWidth() const {
		return width_;
	}

	// return length of Rectangle
	T getLength() const {
		return length_;
	}
private:
	T width_;
	T length_;

};

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Circle : public Shape {
public:
	// constructor for Circle with and name "Circle" and parameter radius
	Circle(double radius) :Shape("Circle") {
		radius_ = radius;
	}

	// return area of Circle
	double getArea() const {
		return M_PI * radius_ * radius_;
	}

	// return volume of Circle
	double getVolume() const {
		return 0;
	}

	// overload operator + to add two Circles
	Circle operator + (const Circle& cir) {
		return Circle(radius_ + cir.getRadius());
	}

	// overload operator - to subtract two Circles
	Circle operator - (const Circle& cir) {
		// if the result is negative for the calculated radius, return 0
		return Circle(max(0.0, radius_ - cir.getRadius()));
	}

	// return radius of Circle
	double getRadius() const {
		return radius_;
	}

private:
	double radius_;

};



//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Sphere : public Shape {
public:
	// constructor for Sphere with name "Sphere" and parameter radius
	Sphere(double radius) :Shape("Sphere") {
		radius_ = radius;
	}

	// return volume of Sphere
	double getVolume() const {
		return 4.0 / 3.0 * M_PI * radius_ * radius_ * radius_;
	}

	// return area of Sphere
	double getArea() const {
		return 4.0 * M_PI * radius_ * radius_;
	}

	// overload operator + to add two Spheres
	Sphere operator + (const Sphere& sph) {
		return Sphere(radius_ + sph.getRadius());
	}

	// overload operator - to subtract two Spheres
	Sphere operator - (const Sphere& sph) {
		// if the result is negative for the calculated radius, return 0
		return Sphere(max(0.0, radius_ - sph.getRadius()));
	}

	// return radius of Sphere
	double getRadius() const {
		return radius_;
	}

private:
	double radius_;

};

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
class RectPrism : public Shape {
public:
	// constructor for RectPrism with name "RectPrism" and parameters width, length, height
	RectPrism(double width, double length, double height) :Shape("RectPrism") {
		width_ = width;
		length_ = length;
		height_ = height;
	}

	// return volume of RectPrism
	double getVolume() const {
		return width_ * length_ * height_;
	}

	// return area of RectPrism
	double getArea() const {
		return 2 * (width_ * length_ + width_ * height_ + length_ * height_);
	}

	// overload operator + to add two RectPrisms
	RectPrism operator + (const RectPrism& rectp) {
		return RectPrism(width_ + rectp.getWidth(), length_ + rectp.getLength(), height_ + rectp.getHeight());
	}

	// overload operator - to subtract two RectPrisms
	RectPrism operator - (const RectPrism& rectp) {
		// if the result is negative for each dimension, return 0 for each
		return RectPrism(
			max(0.0, width_ - rectp.getWidth()),
			max(0.0, length_ - rectp.getLength()),
			max(0.0, height_ - rectp.getHeight())
		);
	}

	// return width of RectPrism
	double getWidth() const {
		return width_;
	}

	// return length of RectPrism
	double getLength() const {
		return length_;
	}

	// return height of RectPrism
	double getHeight() const {
		return height_;
	}

private:
	double length_;
	double width_;
	double height_;

};

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
static list<Shape*> CreateShapes(char* file_name) {
	//@@Insert your code here

	// create a list of Shape pointers
	list<Shape*> shapes;
	// create variables to store the data read from the file
	string name;
	double width, length, height, radius;


	// open the file
	ifstream ifs(file_name, ifstream::in);
	int n;
	// read the number of shapes
	ifs >> n;

	// read the data for each shape and create the corresponding object
	while (n--) {
		// read the name of the shape
		ifs >> name;
		// create the corresponding object and add it to the list
		if (name == "Rectangle") {
			ifs >> width >> length;
			shapes.push_back(new Rectangle<double>(width, length));
		}
		else if (name == "Circle") {
			ifs >> radius;
			shapes.push_back(new Circle(radius));
		}
		else if (name == "Sphere") {
			ifs >> radius;
			shapes.push_back(new Sphere(radius));
		}
		else if (name == "RectPrism") {
			ifs >> width >> length >> height;
			shapes.push_back(new RectPrism(width, length, height));
		}
	}

	// close the file
	ifs.close();

	return shapes;
}

// call getArea() of each object 
// return the max area
static double MaxArea(list<Shape*> shapes) {
	double max_area = 0;
	//@@Insert your code here
	
	// create an iterator to iterate through the list
	list<Shape*>::iterator iter = shapes.begin();

	// iterate through the list and find the max area
	while (iter != shapes.end()) {
		// if the area of the current object is greater than the current max area, update the max area
		if ((*iter)->getArea() > max_area) {
			max_area = (*iter)->getArea();
		}
		// move to the next object
		iter++;
	}

	return max_area;
}

// call getVolume() of each object 
// return the max volume
static double MaxVolume(list<Shape*> shapes) {
	double max_volume = 0;
	//@@Insert your code here
	
	// create an iterator to iterate through the list
	list<Shape*>::iterator iter = shapes.begin();
	// iterate through the list and find the max volume
	while (iter != shapes.end()) {
		// if the volume of the current object is greater than the current max volume, update the max volume
		if ((*iter)->getVolume() > max_volume) {
			max_volume = (*iter)->getVolume();
		}
		// move to the next object
		iter++;
	}

	return max_volume;
}
#endif

