#pragma once

#include <ncl/gl/Scene.h>
#include <ncl/gl/textures.h>


using namespace std;
using namespace glm;
using namespace ncl::gl;

class BoxScene : public Scene {
public:
	BoxScene() :Scene("Box Scene") {
		fBuffer = fBuffer | GL_STENCIL_BUFFER_BIT;
		addShader(GL_VERTEX_SHADER, quad_vert_shader);
		addShader(GL_TESS_EVALUATION_SHADER, quad_tes_shader);
		addShaderFromFile("../shaders/shader.frag");
		angle = 0;
	}

	virtual void init() override {
		texture = new Texture2D("../media/wall2.jpg", 0);
	//	texture1 = new Texture2D("../media/moss.png", 1);
		_shader.sendUniform1ui("img", texture->id());
		_shader.send("useTexture", true);

		planeShader.loadFromstring(GL_VERTEX_SHADER, identity_vert_shader);
		planeShader.loadFromstring(GL_FRAGMENT_SHADER, identity_frag_shader);
		planeShader.createAndLinkProgram();

		Material mat;
		mat.ambient = { 0.1, 0.1, 0.1, 1 };
		mat.diffuse = { 0.9, 0.9, 0.9, 1 };
		mat.specular = { 0.95, 0.95, 0.95, 1 };
		mat.shininess = 1000.0f;

		cube = new Cube;
		teapot = new Teapot;
		plane = new Plane(10, 10, 1.5, 1.5, true, vec4(0, 0, 0, 0.5));
		

		
		
		cam.view = lookAt({ 1.0f, 2.25f, 2.25f }, vec3(0), { 0, 1, 0 });
	//	cam.view = lookAt({ 0, 1.25, 2.25f }, vec3(0), { 0, 1, 0 });
	//	light[0].position = { 1.0f, 1.25f, 1.25f, 1.0f };
		glClearStencil(0);
	}

	virtual void resized() override {
		cam.projection = perspective(radians(60.0f), aspectRatio, 0.3f, 100.0f);
	}

	virtual void display() override {
		mat4 model = rotate(mat4(1), radians(angle), { 0, 1, 0 });
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA);
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_ALWAYS, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilMask(0xFf);
		glDepthMask(0);
		cam.model = translate(model, { -0.2, 0, 0 });;

		planeShader.use();
		planeShader.send(cam);
		plane->draw(planeShader);
		planeShader.unUse();


		glStencilFunc(GL_EQUAL, 1, 1);
		glStencilMask(0xFF);
		
		cam.model = rotate(model, -pi<float>(), { 0, 0, 1 });
	//	cam.model = scale(model, { 1, -1, 1 });
		_shader.send("useTexture", true);
		_shader.send(cam);
		cube->draw(_shader);

		glDisable(GL_STENCIL_TEST);
		glDisable(GL_BLEND);
		glDepthMask(1);
		
		cam.model = model;
		_shader.send("useTexture", true);
		_shader.send(cam);
		cube->draw(_shader);
	}

	virtual void update(float dt) override {
		angle += dt * 20;
		if (angle >= 360) angle -= 360;
	}

private:
	Texture2D* texture;
	Texture2D* texture1;
	Plane* plane;
	Cube* cube;
	Teapot* teapot;
	Shader planeShader;
	float angle;
};