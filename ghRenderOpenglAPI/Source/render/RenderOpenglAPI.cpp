#include <render/RenderOpenglAPI.hpp>
#include <iostream>

namespace ganeshEngine {

void RenderOpenglAPI::lowLevelCall() {
	std::cout << "i am a low level call to the window api GL" << std::endl;
}

}