#include <SFML/Graphics.hpp>
#include <complex>

const int width = 800;
const int height = 600;
const int maxIterations = 100;

const double realConstant = -0.7;
const double imaginaryConstant = 0.27;

int julia(double x, double y) {
     std::complex<double> z(x, y);
     std::complex<double> c(realConstant, imaginaryConstant);

     for(int i = 0; i < maxIterations; i++) {
          z = z * z + c;
          
          if(std::abs(z) > 2) {
               return i;
          }
     }

     return maxIterations;
}

int main() {
     sf::RenderWindow window(sf::VideoMode(800, 600), "Julia Set");
     sf::Image image;
     image.create(width, height, sf::Color::Black);
     sf::Texture texture;
     sf::Sprite sprite;
     
     for(int x = 0; x < width; x++) {
          for(int y = 0; y < height; y++) {
               double real = (x - width / 2.0) * 4 / width;
               double imaginary = (y - height / 2.0) * 4 / height;
               int iteration = julia(real, imaginary);
               
               if (iteration == maxIterations) {
                    image.setPixel(x, y, sf::Color::Black);
               } else {
                    float ratio = static_cast<float>(iteration) / maxIterations;
                    
                    int intensity = static_cast<int>(255 * ratio);
                    image.setPixel(x, y, sf::Color(intensity, intensity, intensity));
               }
          }
     }

     texture.loadFromImage(image);
     sprite.setTexture(texture);

     while(window.isOpen()) {
          sf::Event event;
          while(window.pollEvent(event)) {
               if(event.type == sf::Event::Closed) {
                    window.close();
               }
          
          }

          window.clear();
          window.draw(sprite);
          window.display();
     }

     return 0;
}
