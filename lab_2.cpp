#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Person_class.cpp"
#include "IDictionary.cpp"

#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void DistibutionOfPeople(std::vector<int> distribution, IDictionary<int, int>& dictionary, std::vector<Person> Persons, int index);
void output(int flag, std::vector<std::pair<std::string, std::vector<float>>> ColorMatrix, const std::vector<std::pair<std::string, IDictionary<int, int>>>& DictionaryMatrix);
void menu(int& flag_check, std::vector<std::pair<std::string, std::vector<int>>>& DistributionMatrix);
void FillMatrix(int size, int index, std::vector<std::pair<std::string, std::vector<int>>>& DistributionMatrix);
void Draw(int& start, int size, int sq_cons, int flag, int shaderProgram, std::vector<std::pair<std::string, std::vector<float>>> ColorMatrix, const std::vector<std::pair<std::string, IDictionary<int, int>>>& DictionaryMatrix);
void FillPartitionBoundaries(std::vector<std::pair<std::string, std::vector<int>>> DistributionMatrix,  std::vector<Person>& Persons);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 model;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = model * vec4(aPos, 1.0);\n"
	"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"uniform vec4 ourColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = ourColor;\n"
	"}\n\0";


int main() {
    int square_number = 100;
    int sq_cons = square_number * square_number / 100;
    int size_v = square_number*square_number*6*3;
    float vertices[size_v];
    float width = 1.6;
    float a = width / square_number;
    float point_y = -0.8;
    float point_x = -0.8;
    float start_point_x = -0.8;
    int flag_1 = 0;
    int x0 = 0.0;
    int y0 = 0.0;
    int z0 = 0.0;
    float R = 0.8;
    float vertices_sphere[size_v];

    for (int i = 0; i < size_v; i+=18) {
        vertices[i] = point_x; vertices[i+1] = point_y; vertices[i+2] = 0.0;
        vertices[i+3] = point_x + a; vertices[i+4] = point_y; vertices[i+5] = 0.0;
        vertices[i+6] = point_x + a; vertices[i+7] = point_y + a; vertices[i+8] = 0.0;
        vertices[i+9] = point_x; vertices[i+10] = point_y; vertices[i+11] = 0.0;
        vertices[i+12] = point_x; vertices[i+13] = point_y + a; vertices[i+14] = 0.0;
        vertices[i+15] = point_x + a; vertices[i+16] = point_y + a; vertices[i+17] = 0.0;
        flag_1 += 1;
        point_x += a;
        if (flag_1 == square_number) {
            point_y += a;
            flag_1 = 0;
            point_x = start_point_x;
        }
    }

    for (int i = 0; i < size_v; i+=3) {
        float phi = (vertices[i] + 0.8) * M_PI * 2 / 1.6;
        float teta = (vertices[i+1] + 0.8) * M_PI / 1.6;
        vertices_sphere[i] = R * sin(teta) * cos(phi);
        vertices_sphere[i+1] = R * sin(teta) * sin(phi);
        vertices_sphere[i+2] = R * cos(teta); 
    }

    std::vector<std::pair<std::string, std::vector<float>>> ColorMatrix = {
        {"Пурпурный", {0.4f, 0.18f, 0.31f}},
        {"Темно-cиний", {0.1f, 0.15f, 0.27f}},
        {"Синий", {0.22f, 0.28f, 0.52f}},
        {"Сиреневый", {0.46f, 0.41f, 0.65f}},
        {"Ламантин", {0.6f, 0.55f, 0.67f}}
    };

    srand(time(NULL));

    int size = 100;
    int flag_check;
    int z = 1;
    while(z == 1) {
        std::vector<std::pair<std::string, std::vector<int>>> DistributionMatrix = { 
            {"Разбиение по возрасту:\n", {0, 24, 48, 72, 96, 120}},
            {"Разбиение по росту:\n", {90, 115, 140, 165, 190, 215}},
            {"Разбиение по весу:\n", {40, 55, 70, 85, 100, 115}} 
        };

        std::vector<std::pair<std::string, std::vector<int>>> DistributionMatrix_1 = { 
            {"Разбиение по возрасту:\n", {}},
            {"Разбиение по росту:\n", {}},
            {"Разбиение по весу:\n", {}} 
        };

        std::vector<std::pair<std::string, IDictionary<int, int>>> DictionaryMatrix = {
            {"По возрасту:\n", {}},
            {"По росту:\n", {}},
            {"По весу:\n", {}}
        };

        menu(flag_check, DistributionMatrix_1);

        if (flag_check == 0)
            break;

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    
        glewExperimental = true;

        if (glewInit() != GLEW_OK) {
            fprintf(stderr, "Невозможно инициализировать GLEW\n");
            return -1;
        }

        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        std::vector<Person> Persons(size);

        if (flag_check == 1) {
            FillPartitionBoundaries(DistributionMatrix, Persons);
            for (int i = 0; i < DistributionMatrix.size(); i++) {
                DistibutionOfPeople(DistributionMatrix[i].second, DictionaryMatrix[i].second, Persons, i);
            }
        }

        if (flag_check == 2) {
            FillPartitionBoundaries(DistributionMatrix_1, Persons);
            for (int i = 0; i < DistributionMatrix.size(); i++) {
                DistibutionOfPeople(DistributionMatrix_1[i].second, DictionaryMatrix[i].second, Persons, i);
            }
        }

        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_sphere), vertices_sphere, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(VAO);

        int flag = -1;
        int check = 0;

        while(!glfwWindowShouldClose(window)) {
            processInput(window);

            glClearColor(0.92f, 0.86f, 0.78f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glUseProgram(shaderProgram);

            if (check%700 == 0) {
                flag += 1;
                if (flag == 3) 
                    flag = 0;

                output(flag, ColorMatrix, DictionaryMatrix);

                check = 1;  
 
            }

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(30.0f, -20.0f, 30.0f));
            int vertexModelLocation = glGetUniformLocation(shaderProgram, "model");
            glUniformMatrix4fv(vertexModelLocation, 1, GL_FALSE, glm::value_ptr(model));

            int start = 0;
            Draw(start, size, sq_cons, flag, shaderProgram, ColorMatrix, DictionaryMatrix); 

            glfwSwapBuffers(window);
            glfwPollEvents();

            check += 1;
        }

        glDeleteVertexArrays(1, &VAO); 
        glDeleteBuffers(1, &VBO);
        glfwTerminate();
    }
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Draw(int& start, int size, int sq_cons, int flag, int shaderProgram, std::vector<std::pair<std::string, std::vector<float>>> ColorMatrix, const std::vector<std::pair<std::string, IDictionary<int, int>>>& DictionaryMatrix) {
    for (int j = 0; j < DictionaryMatrix[flag].second.GetSize() - 1; j++) {
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, ColorMatrix[j].second[0], ColorMatrix[j].second[1], ColorMatrix[j].second[2], 1.0f);

        glDrawArrays(GL_TRIANGLES, start, start + 6 * sq_cons*(DictionaryMatrix[flag].second.Get(j))/size*100);
        start += 6*sq_cons*(DictionaryMatrix[flag].second.Get(j))/size*100;
    }
}

void FillPartitionBoundaries(std::vector<std::pair<std::string, std::vector<int>>> DistributionMatrix,  std::vector<Person>& Persons) {
    int first_age = DistributionMatrix[0].second[0];
    int last_age = DistributionMatrix[0].second[sizeof(DistributionMatrix[0].second)/sizeof(int) -1] - first_age;

    int first_height = DistributionMatrix[1].second[0];
    int last_height =  DistributionMatrix[1].second[sizeof(DistributionMatrix[1].second)/sizeof(int) -1] - first_height;

    int first_mass = DistributionMatrix[2].second[0];
    int last_mass = DistributionMatrix[2].second[sizeof(DistributionMatrix[2].second)/sizeof(int) -1] - first_mass;

        
    for (auto &person:Persons) {
        person.SetInfo({first_age + 1 + rand()% last_age - 1, first_height + 1 + rand()% last_height - 1, first_mass + 1 + rand()% last_mass - 1 });
    }
} 

void output(int flag, std::vector<std::pair<std::string, std::vector<float>>> ColorMatrix, const std::vector<std::pair<std::string, IDictionary<int, int>>>& DictionaryMatrix) {
    std::cout << DictionaryMatrix[flag].first;

    for (int i = 0; i < DictionaryMatrix[flag].second.GetSize() - 1; i++ ) {
        std::cout << ColorMatrix[i].first << " - " << DictionaryMatrix[flag].second.Get(i) << "\n";
    }
    
    std::cout << "\n";
}

void menu(int& flag_check, std::vector<std::pair<std::string, std::vector<int>>>& DistributionMatrix) {
    std::cout << "Введите 1, если хотите начать работу с программой <Гистрограмма>, гистограмма будет строиться по списку из 100 человек равноменрным разбиением\n";
    std::cout << "Введите 2, если хотите начать работу с программой <Гистрограмма>, гистограмма будет строиться по списку из 100 человек с кастомным разбиением\n";
    std::cout << "Если вы хотите закончить работать с программой введите 0\n";
    std::cin >> flag_check;

    if (flag_check == 2) {
        int size_age = 6;
        int size_height = 6;
        int size_mass = 6;

        std::cout << "\nВ каждом разделе вам надо ввести 6 чисел для границ разбиения\n";

        std::cout << "Введите границы разбиения по возрасту\n";
        FillMatrix(size_age, 0, DistributionMatrix);

        std::cout << "\nВведите границы разбиения по росту\n";
        FillMatrix(size_height, 1, DistributionMatrix);

        std::cout << "\nВведите границы разбиения по весу\n";
        FillMatrix(size_mass, 2, DistributionMatrix);

    }
    std::cout << "\n";
}

void FillMatrix(int size, int index, std::vector<std::pair<std::string, std::vector<int>>>& DistributionMatrix) {
    for (int i = 0; i < size; i ++) {
        int number;
        std::cin >> number;
        DistributionMatrix[index].second.push_back(number);
    }
}

void DistibutionOfPeople(std::vector<int> distribution, IDictionary<int, int>& dictionary, std::vector<Person> Persons, int index) {
    for (int i = 0; i < distribution.size(); i++)
            dictionary.Add(i, 0);

        for (auto &person:Persons) {
            for (int i = 0; i < distribution.size(); i++) {
                if (distribution[i] <= person.Get(index) && distribution[i+1] > person.Get(index)) {
                    dictionary.Get(i) += 1;
                }  
            }
        }
}
