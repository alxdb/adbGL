//
// Created by Alexander Davidson Bryan on 10/07/2018.
//

#include <exception>
#include <iostream>

#include <Core.h>

int main() {
	Window window(500, 500, "BasicTriangle");
	window.makeCurrent();
	window.setClearColor(0.3, 0.2, 0.5, 1.0);
	while (!window.shouldClose()) {
		window.update();
	}
}
