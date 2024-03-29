#include <fstream>
#include <chrono>
#include <thread>

#if defined(_WIN32) || defined(_WIN64)
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

#include "develop-3-Game.hh"

const GLfloat Game::v_triangle[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};
const GLfloat Game::v_rectangle[] = {
        // first triangle
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, 0.5f, 0.0f, // top left
        // second triangle
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f // top left
    };
const GLfloat Game::v_rectangle_ebo_2[] = {
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f // top left
    };
const GLuint Game::v_rectangle_indexs[] = { // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3 // second triangle
    };

const GLfloat Game::v_triangle_2[] = {
    // positions       // colors
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
    0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top
};
const GLfloat Game::v_triangle_texture[] = {
        0.0f, 0.0f, // lower-left corner
        1.0f, 0.0f, // lower-right corner
        0.5f, 1.0f // top-center corner
    };
const GLfloat Game::v_rectangle_textured[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };
const GLfloat Game::v_cube[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

bool Game::initialize(const char* title, int width, int height)
{
    // Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if( window == NULL )
    {
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
    {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//GLuint VertexArrayID;
	//std::cout << "vbID_tirangle : " << vbID_tirangle << "\n";
	glGenVertexArrays(1, &vao);
	//std::cout << "vbID_tirangle : " << vbID_tirangle << "\n";
	glBindVertexArray(vao);

	// Create and compile our GLSL program from the shaders
	shader_0 = LoadShaders( "tests/triangle/SimpleVertexShader-0.vertexshader", "tests/triangle/SimpleFragmentShader-0.fragmentshader");
	shader_1 = LoadShaders( "tests/triangle/SimpleVertexShader-1.vertexshader", "tests/triangle/SimpleFragmentShader-1.fragmentshader");
	//shader_2 = LoadShaders( "tests/triangle/SimpleVertexShader-2.vertexshader", "tests/triangle/SimpleFragmentShader-2.fragmentshader");
    shader_2.build( "tests/triangle/SimpleVertexShader-2.vertexshader", "tests/triangle/SimpleFragmentShader-2.fragmentshader");
    shader_text.build("tests/text.vertex", "tests/textfragment");

	glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//std::cout << "vsID_triangle : " << vsID_triangle << "\n";
	glGenBuffers(1, &vbo_triangle);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v_triangle), v_triangle, GL_STATIC_DRAW);
	//std::cout << "vsID_triangle : " << vsID_triangle << "\n";
	glGenBuffers(1, &vbo_triangle_2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle_2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v_triangle_2), v_triangle_2, GL_STATIC_DRAW);
	//std::cout << "vsID_triangle : " << vsID_triangle << "\n";
	glGenBuffers(1, &vbo_rectangle);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_rectangle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v_rectangle), v_rectangle, GL_STATIC_DRAW);
	//std::cout << "vsID_triangle : " << vsID_triangle << "\n";
	glGenBuffers(1, &vbo_cube);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v_cube), v_cube, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo_rectangle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_rectangle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(v_rectangle_indexs), v_rectangle_indexs, GL_STATIC_DRAW);
	glGenBuffers(1, &ebo_rectangle_textured);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_rectangle_textured);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(v_rectangle_indexs), v_rectangle_indexs, GL_STATIC_DRAW);


	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(shader_1, "MVP");

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

	camera = glm::vec3(4,3,3);//posision de la camara
	step = 0;

	// Camera matrix
	/*view       = glm::lookAt(
								camera, // Camera is at (4,3,3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );*/
	// Model matrix : an identity matrix (model will be at the origin)
	model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	//mvp        = projection * view * model;

	fps_ms = std::chrono::milliseconds(int(1.0/60.0)/1000);
	step_trans = 0;
	action_main = NULL;
	action_shape = NULL;

	//uniform shader
	vertexColorLocation = glGetUniformLocation(shader_1, "ourColor");

    camera_target =  glm::vec3(0,0,0);
    camera_direction = glm::normalize(camera - camera_target);
    camera_rigth = glm::normalize(glm::cross(glm::vec3(0,1,0), camera_direction));
    camera_up = glm::cross(camera_direction, camera_rigth);
    //camera_up = glm::vec3(0,1,0);
    camera_rotate = false;
    camera_radius = glm::distance(camera,camera_target);

    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return false;
    }
    if (FT_New_Face(ft, "fonts/truetype/dejavu/DejaVuSans.ttf", 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return false;
    }
    else
    {
        // set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, 48);

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // load first 128 characters of ASCII set
        for (unsigned char c = 0; c < 128; c++)
        {
            // Load character glyph
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    FT_Set_Pixel_Sizes(face, 0, 48);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    // configure VAO/VBO for texture quads
    // -----------------------------------
    //glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &vbo_text);
    //glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_text);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);

	running = true;
    return true;
}

void Game::handleEvents()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS or glfwWindowShouldClose(window) != 0 )
    {
        running = false;
    }
    else if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        action_main = &Game::action_align;
    }
    else if(glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        action_shape = &Game::action_create_triangle;
    }
    else if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        camera.x -= 0.01;
    }
    else if(glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        camera.y -= 0.01;
    }
    else if(glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        camera.z -= 0.01;
    }
    else if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        action_shape = &Game::action_create_rectangle;
    }
    else if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        camera_rotate = !camera_rotate;
    }
    else if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        camera_radius += 0.05;
    }
    else if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        action_shape = &Game::action_cube;
    }
}

void Game::update()
{
    if(camera_rotate) action_rotate_scene();

    view       = glm::lookAt(
								camera, // Camera is at (4,3,3), in World Space
								camera_target, // and looks at the origin
								camera_up  // Head is up (set to 0,-1,0 to look upside-down)
						   );
    mvp        = projection * view * model;


    // Clear the screen
    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    RenderText(shader_text, "This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));

    // Use our shader
    //glUseProgram(shader_1);
    //glBindVertexArray(vao);

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

    // 1rst attribute buffer : vertices
    if(action_shape) (this->*action_shape)();
    if(action_main) (this->*action_main)();


}

void Game::rendering()
{
    handleEvents();
    update();
    glfwSwapBuffers(window);
    glfwPollEvents();

    std::this_thread::sleep_for(std::chrono::milliseconds(fps_ms));
}

void Game::clean()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo_triangle);
    glDeleteBuffers(1, &ebo_rectangle);
    glDeleteBuffers(1, &vbo_triangle_2);
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}







GLuint Game::LoadShaders(const char * vertex_file_path,const char * fragment_file_path)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}


void Game::action_align()
{
    if(camera.x > 0) camera.x -= 0.01;
    else step = 1;
}
void Game::action_create_triangle()
{

    timeValue = glfwGetTime();
    greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    //vertexColorLocation = glGetUniformLocation(programID, "ourColor");
    glUniform3f(vertexColorLocation, 0.0f, greenValue, 0.0f);

    glUseProgram(shader_1);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
    glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

    glDisableVertexAttribArray(0);
}

void Game::action_x()
{
    camera.x -= 0.01;
}

void Game::action_create_rectangle()
{
    timeValue = glfwGetTime();
    greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    //vertexColorLocation = glGetUniformLocation(programID, "ourColor");
    glUniform3f(vertexColorLocation, 0.0f, greenValue, 0.0f);

    glUseProgram(shader_1);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_rectangle);
    glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);
}
void Game::action_create_rectangle_2()
{

    timeValue = glfwGetTime();
    greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    //vertexColorLocation = glGetUniformLocation(programID, "ourColor");
    glUniform3f(vertexColorLocation, 0.0f, greenValue, 0.0f);

    glUseProgram(shader_1);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_rectangle);
    glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);
}
void Game::action_create_triangle_2()
{
    glUseProgram(shader_2);

    //glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle_2);
    glBindVertexArray(vao);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}


void Game::action_create_rectangle_textured()
{
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

}

void Game::action_rotate_scene()
{
    camera.y = sin(glfwGetTime()) * camera_radius;
    camera.z = cos(glfwGetTime()) * camera_radius;

    //if(camera.x > 0) camera.x -= 0.01;
    /*
    camera_direction = glm::normalize(camera - camera_target);
    camera_rigth = glm::normalize(glm::cross(glm::vec3(0,1,0), camera_direction));
    camera_up = glm::cross(camera_direction, camera_rigth);
    */
}





void Game::action_cube()
{
    timeValue = glfwGetTime();
    greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    //vertexColorLocation = glGetUniformLocation(programID, "ourColor");
    glUniform3f(vertexColorLocation, 0.0f, greenValue, 0.0f);

    glUseProgram(shader_1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glDisableVertexAttribArray(0);
}



void Game::RenderText(verso_here::Shader &s, std::string text, float x, float y, float scale, glm::vec3 color)
{
    // activate corresponding render state
    s.use();
    glUniform3f(glGetUniformLocation(s, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_text);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
