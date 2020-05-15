#include "GSSetting.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern int clickstat;

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
	button->Set2DPosition(screenWidth / 2, 500);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(button);

	//mute button
	texture = ResourceManagers::GetInstance()->GetTexture("mute_btn");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 300);
	button->SetSize(110, 100);
	button->SetOnClick([]() {
		ResourceManagers::GetInstance()->PauseSound("Twister-Tetris");
	});
	m_listButton.push_back(button);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("telelower");
	m_Text_gameName = std::make_shared< Text>(shader, font, "SETTING", TEXT_COLOR::GREEN, 1.7);
	m_Text_gameName->Set2DPosition(Vector2(screenWidth / 2 - 80, 120));
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
	//unmute button
	auto texture = ResourceManagers::GetInstance()->GetTexture("unmute_btn");
	std::shared_ptr<GameButton> unmute_btn = std::make_shared<GameButton>(model, shader, texture);
	unmute_btn->Set2DPosition(screenWidth / 2, 300);
	unmute_btn->SetSize(110, 100);
	unmute_btn->SetOnClick([]() {
		ResourceManagers::GetInstance()->PlaySound("Twister-Tetris", true);
	});

	//mute button
	texture = ResourceManagers::GetInstance()->GetTexture("mute_btn");
	std::shared_ptr<GameButton> mute_btn = std::make_shared<GameButton>(model, shader, texture);
	mute_btn->Set2DPosition(screenWidth / 2, 300);
	mute_btn->SetSize(110, 100);
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
}

void GSSetting::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_gameName->Draw();
}
