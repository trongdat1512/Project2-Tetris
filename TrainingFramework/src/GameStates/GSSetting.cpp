#include "GSSetting.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern int clickstat;
extern bool isMuted;

GSSetting::GSSetting()
{

}


GSSetting::~GSSetting()
{
}



void GSSetting::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("setting_background");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//back button
	texture = ResourceManagers::GetInstance()->GetTexture("back_btn");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 550);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(button);

	//backgroud music mute button
	texture = ResourceManagers::GetInstance()->GetTexture("mute_btn");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 250);
	button->SetSize(77, 70);
	button->SetOnClick([]() {
		ResourceManagers::GetInstance()->PauseSound("Twister-Tetris");
	});
	m_listButton.push_back(button);

	//sound effects mute button
	texture = ResourceManagers::GetInstance()->GetTexture("mute_btn");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 400);
	button->SetSize(77, 70);
	button->SetOnClick([]() {
		isMuted = true;
	});
	m_listButton2.push_back(button);

	//text setting title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("telelower");
	std::shared_ptr<Text> text = std::make_shared< Text>(shader, font, "SETTING", TEXT_COLOR::BLUE, 1.7);
	text->Set2DPosition(Vector2(screenWidth / 2 - 80, 120));
	m_listText.push_back(text);

	text = std::make_shared< Text>(shader, font, "Background Music", TEXT_COLOR::BLUE, 1.2);
	text->Set2DPosition(Vector2(screenWidth / 2 - 120, 200));
	m_listText.push_back(text);

	text = std::make_shared< Text>(shader, font, "Sound Effects", TEXT_COLOR::BLUE, 1.2);
	text->Set2DPosition(Vector2(screenWidth / 2 - 100, 350));
	m_listText.push_back(text);
}

void GSSetting::Exit()
{
}


void GSSetting::Pause()
{

}

void GSSetting::Resume()
{

}


void GSSetting::HandleEvents()
{

}

void GSSetting::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSSetting::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	if (!clickstat) {
		//do something
		for (auto it : m_listButton)
		{
			(it)->HandleTouchEvents(x, y, bIsPressed);
			if ((it)->IsHandle()) break;
		}
		for (auto it : m_listButton2)
		{
			(it)->HandleTouchEvents(x, y, bIsPressed);
			if ((it)->IsHandle()) break;
		}
		clickstat = 1;
	}
	else {
		clickstat = 0;
	}
}

void GSSetting::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	//background music unmute button
	auto texture = ResourceManagers::GetInstance()->GetTexture("unmute_btn");
	std::shared_ptr<GameButton> unmute_btn = std::make_shared<GameButton>(model, shader, texture);
	unmute_btn->Set2DPosition(screenWidth / 2, 250);
	unmute_btn->SetSize(77, 70);
	unmute_btn->SetOnClick([]() {
		ResourceManagers::GetInstance()->PlaySound("Twister-Tetris", true);
	});

	//background music mute button
	texture = ResourceManagers::GetInstance()->GetTexture("mute_btn");
	std::shared_ptr<GameButton> mute_btn = std::make_shared<GameButton>(model, shader, texture);
	mute_btn->Set2DPosition(screenWidth / 2, 250);
	mute_btn->SetSize(77, 70);
	mute_btn->SetOnClick([]() {
		ResourceManagers::GetInstance()->PauseSound("Twister-Tetris");
	});

	if (ResourceManagers::GetInstance()->isPlaying("Twister-Tetris")) {
		m_listButton.pop_back();
		m_listButton.push_back(mute_btn);
	}
	else {
		m_listButton.pop_back();
		m_listButton.push_back(unmute_btn);
	}

	//sound effects unmute button
	texture = ResourceManagers::GetInstance()->GetTexture("unmute_btn");
	unmute_btn = std::make_shared<GameButton>(model, shader, texture);
	unmute_btn->Set2DPosition(screenWidth / 2, 400);
	unmute_btn->SetSize(77, 70);
	unmute_btn->SetOnClick([]() {
		isMuted = false;
	});

	//sound effects mute button
	texture = ResourceManagers::GetInstance()->GetTexture("mute_btn");
	mute_btn = std::make_shared<GameButton>(model, shader, texture);
	mute_btn->Set2DPosition(screenWidth / 2, 400);
	mute_btn->SetSize(77, 70);
	mute_btn->SetOnClick([]() {
		isMuted = true;
	});

	if (!isMuted) {
		m_listButton2.pop_back();
		m_listButton2.push_back(mute_btn);
	}
	else {
		m_listButton2.pop_back();
		m_listButton2.push_back(unmute_btn);
	}
}

void GSSetting::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_listButton2)
	{
		it->Draw();
	}
	for (auto it : m_listText)
	{
		it->Draw();
	}
}
