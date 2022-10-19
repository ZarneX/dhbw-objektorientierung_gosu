#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <vector>
#include <Windows.h>
#include <iostream>

using namespace std;

class GameWindow : public Gosu::Window
{
public:

	GameWindow()
		: Window(1920, 1080, true)
		, walk_anim("Walk_DownRight1.png")
		, up_right1("Enemy_UpRight1.png")
		, up_right2("Enemy_UpRight2.png")
		, up_right3("Enemy_UpRight3.png")
		, up_left1("Enemy_UpLeft1.png")
		, up_left2("Enemy_UpLeft2.png")
		, up_left3("Enemy_UpLeft3.png")
		, down_right1("Enemy_DownRight1.png")
		, down_right2("Enemy_DownRight2.png")
		, down_right3("Enemy_DownRight3.png")
		, down_left1("Enemy_DownLeft1.png")
		, down_left2("Enemy_DownLeft2.png")
		, down_left3("Enemy_DownLeft3.png")
		, grass("Grass_Tile.png")
		, full_heart("Full_Heart.png")
		, half_heart("Half_Heart.png")
		, empty_heart("Empty_Heart.png")
		, attack_bar("Attack_Bar.png")
		, stamina_bar("Stamina_Bar.png")
		, titlescreen("Titlescreen.png")
		, gameover_char("GameOver.png")
	{
		set_caption("Gosu Tutorial mit Git");
	}

	Gosu::Image up_right1;
	Gosu::Image up_right2;
	Gosu::Image up_right3;
	Gosu::Image up_left1; 
	Gosu::Image up_left2; 
	Gosu::Image up_left3; 
	Gosu::Image down_right1;
	Gosu::Image down_right2;
	Gosu::Image down_right3;
	Gosu::Image down_left1;
	Gosu::Image down_left2;
	Gosu::Image down_left3;

	Gosu::Image grass;

	Gosu::Image full_heart;
	Gosu::Image half_heart;
	Gosu::Image empty_heart;
	Gosu::Image attack_bar;
	Gosu::Image stamina_bar;

	Gosu::Image titlescreen;
	Gosu::Image gameover_char;

	struct enemy
	{
	public: 
		float x;
		float y;
		int walk_count;
	};

	vector<enemy> enemies;
	int points = 0;
	int lives = 6;
	bool hit = false;
	int hit_counter = 0;
	bool game_over = false;
	bool game_start = false;
	bool pause = false;

	int attack_meter = 0;
	double stamina_meter = 300.0;

	Gosu::Image walk_anim;

	double grass_x;
	double grass_y;

	// Wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{
		if (!game_over && game_start && !pause) {

			grass.draw(-24.0 + grass_x, -23.0 + grass_y, -10);

			if ((current_state == "Attack_DownLeft" || current_state == "HurtAttack_DownLeft" ||
				current_state == "Attack_UpLeft" || current_state == "HurtAttack_UpLeft") &&
				(attack_state == 2 || attack_state == 3))
				walk_anim.draw(915, 525, 2);
			else if (super_attack && attack_state >= 5 && attack_state <= 9)
				walk_anim.draw(930, 525, 2);
			else
				walk_anim.draw(945, 525, 2);

			Gosu::Font font(34, "m5x7");
			font.draw_text("Score: " + to_string(points), 10, 10, 10, 1.0, 1.0, Gosu::Color::from_hsv(0, 0, 0.102));

			if (lives == 6) {
				full_heart.draw(1876, 10, 10);
				full_heart.draw(1843, 10, 10);
				full_heart.draw(1810, 10, 10);
			}
			else if (lives == 5) {
				half_heart.draw(1876, 10, 10);
				full_heart.draw(1843, 10, 10);
				full_heart.draw(1810, 10, 10);
			}
			else if (lives == 4) {
				empty_heart.draw(1876, 10, 10);
				full_heart.draw(1843, 10, 10);
				full_heart.draw(1810, 10, 10);
			}
			else if (lives == 3) {
				empty_heart.draw(1876, 10, 10);
				half_heart.draw(1843, 10, 10);
				full_heart.draw(1810, 10, 10);
			}
			else if (lives == 2) {
				empty_heart.draw(1876, 10, 10);
				empty_heart.draw(1843, 10, 10);
				full_heart.draw(1810, 10, 10);
			}
			else if (lives == 1) {
				empty_heart.draw(1876, 10, 10);
				empty_heart.draw(1843, 10, 10);
				half_heart.draw(1810, 10, 10);
			}

			attack_bar.draw(1698, 10, 10);
			graphics().draw_rect(1700.0 + (double(attack_meter)/100.0 * 99.0), 11.0, 99.0 - (double(attack_meter) / 100.0 * 99.0), 14.0, Gosu::Color::from_hsv(0, 0, 0.102), 11);
			stamina_bar.draw(1698, 27, 10);
			graphics().draw_rect(1700.0 + (stamina_meter / 300.0 * 99.0), 28.0, 99.0 - (stamina_meter / 300.0 * 99.0), 14.0, Gosu::Color::from_hsv(0, 0, 0.102), 11);


			for (size_t i = 0; i < enemies.size(); i++) {

				if (enemies.at(i).walk_count == 0) {
					if (enemies.at(i).x <= 960 && enemies.at(i).y >= 540)
						up_right1.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x <= 960 && enemies.at(i).y < 540)
						down_right1.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x > 960 && enemies.at(i).y < 540)
						down_left1.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x > 960 && enemies.at(i).y >= 540)
						up_left1.draw(enemies.at(i).x, enemies.at(i).y, 1);
				}
				else if (enemies.at(i).walk_count == 1) {
					if (enemies.at(i).x <= 960 && enemies.at(i).y >= 540)
						up_right2.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x <= 960 && enemies.at(i).y < 540)
						down_right2.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x > 960 && enemies.at(i).y < 540)
						down_left2.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x > 960 && enemies.at(i).y >= 540)
						up_left2.draw(enemies.at(i).x, enemies.at(i).y, 1);
				}
				else if (enemies.at(i).walk_count == 2) {
					if (enemies.at(i).x <= 960 && enemies.at(i).y >= 540)
						up_right1.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x <= 960 && enemies.at(i).y < 540)
						down_right1.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x > 960 && enemies.at(i).y < 540)
						down_left1.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x > 960 && enemies.at(i).y >= 540)
						up_left1.draw(enemies.at(i).x, enemies.at(i).y, 1);
				}
				else if (enemies.at(i).walk_count == 3) {
					if (enemies.at(i).x <= 960 && enemies.at(i).y >= 540)
						up_right3.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x <= 960 && enemies.at(i).y < 540)
						down_right3.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x > 960 && enemies.at(i).y < 540)
						down_left3.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x > 960 && enemies.at(i).y >= 540)
						up_left3.draw(enemies.at(i).x, enemies.at(i).y, 1);
				}
			}
		}
		else if (game_over) {
			grass.draw(-24.0 + grass_x, -23.0 + grass_y, -10);

			gameover_char.draw(910, 250);

			Gosu::Font font_titlescreen(100, "m5x7");

			font_titlescreen.draw_text_rel("Game", 960, 100, 0, 0.5, 0.5, 1.0, 1.0, Gosu::Color::from_hsv(0, 0, 0.102));
			font_titlescreen.draw_text_rel("Over", 960, 200, 0, 0.5, 0.5, 1.0, 1.0, Gosu::Color::from_hsv(0, 0, 0.102));

			Gosu::Font font_score(50, "m5x7");

			font_score.draw_text_rel("Score: " + to_string(points), 960, 450, 0, 0.5, 0.5, 1.0, 1.0, Gosu::Color::from_hsv(0, 0, 0.102));

			Gosu::Font font_start(30, "m5x7");

			if (input().mouse_x() > 882 && input().mouse_x() < 1038 && input().mouse_y() > 522 && input().mouse_y() < 568) {
				font_start.draw_text_rel("Retry", 960, 545, 0, 0.5, 0.5, 1.0, 1.0, Gosu::Color::from_hsv(0, 0, 0.306));
				graphics().draw_rect(880, 520, 160, 50, Gosu::Color::from_hsv(0, 0, 0.306), -2);
				graphics().draw_rect(882, 522, 156, 46, Gosu::Color::from_hsv(0, 0, 0.102), -2);
			}
			else {
				font_start.draw_text_rel("Retry", 960, 545, 0, 0.5, 0.5, 1.0, 1.0, Gosu::Color::from_hsv(0, 0, 0.102));
				graphics().draw_rect(880, 520, 160, 50, Gosu::Color::from_hsv(0, 0, 0.102), -2);
				graphics().draw_rect(882, 522, 156, 46, Gosu::Color::from_hsv(0, 0, 0.306), -2);
			}

			if (input().mouse_x() > 882 && input().mouse_x() < 1038 && input().mouse_y() > 582 && input().mouse_y() < 628) {
				font_start.draw_text_rel("Exit", 960, 605, 0, 0.5, 0.5, 1.0, 1.0, Gosu::Color::from_hsv(0, 0, 0.306));
				graphics().draw_rect(880, 580, 160, 50, Gosu::Color::from_hsv(0, 0, 0.306), -2);
				graphics().draw_rect(882, 583, 156, 45, Gosu::Color::from_hsv(0, 0, 0.102), -2);
			}
			else {
				font_start.draw_text_rel("Exit", 960, 605, 0, 0.5, 0.5, 1.0, 1.0, Gosu::Color::from_hsv(0, 0, 0.102));
				graphics().draw_rect(880, 580, 160, 50, Gosu::Color::from_hsv(0, 0, 0.102), -2);
				graphics().draw_rect(882, 583, 156, 45, Gosu::Color::from_hsv(0, 0, 0.306), -2);
			}

		}
		else if (!game_start) {
			grass.draw(-24.0 + grass_x, -23.0 + grass_y, -10);

			titlescreen.draw(900, 300);

			Gosu::Font font_titlescreen(100, "m5x7");

			font_titlescreen.draw_text_rel("Goblin", 960, 100, 0, 0.5, 0.5, 1.0, 1.0, Gosu::Color::from_hsv(0, 0, 0.102));
			font_titlescreen.draw_text_rel("Survivor", 960, 200, 0, 0.5, 0.5, 1.0, 1.0, Gosu::Color::from_hsv(0, 0, 0.102));

			Gosu::Font font_start(30, "m5x7");

			if (input().mouse_x() > 882 && input().mouse_x() < 1038 && input().mouse_y() > 522 && input().mouse_y() < 568) {
				font_start.draw_text_rel("Start Game", 960, 545, 0, 0.5, 0.5, 1.0, 1.0, Gosu::Color::from_hsv(0, 0, 0.306));
				graphics().draw_rect(880, 520, 160, 50, Gosu::Color::from_hsv(0, 0, 0.306), -2);
				graphics().draw_rect(882, 522, 156, 46, Gosu::Color::from_hsv(0, 0, 0.102), -2);
			}
			else {
				font_start.draw_text_rel("Start Game", 960, 545, 0, 0.5, 0.5, 1.0, 1.0, Gosu::Color::from_hsv(0, 0, 0.102));
				graphics().draw_rect(880, 520, 160, 50, Gosu::Color::from_hsv(0, 0, 0.102), -2);
				graphics().draw_rect(882, 522, 156, 46, Gosu::Color::from_hsv(0, 0, 0.306), -2);
			}

			if (input().mouse_x() > 882 && input().mouse_x() < 1038 && input().mouse_y() > 582 && input().mouse_y() < 628) {
				font_start.draw_text_rel("Exit", 960, 605, 0, 0.5, 0.5, 1.0, 1.0, Gosu::Color::from_hsv(0, 0, 0.306));
				graphics().draw_rect(880, 580, 160, 50, Gosu::Color::from_hsv(0, 0, 0.306), -2);
				graphics().draw_rect(882, 583, 156, 45, Gosu::Color::from_hsv(0, 0, 0.102), -2);
			}
			else {
				font_start.draw_text_rel("Exit", 960, 605, 0, 0.5, 0.5, 1.0, 1.0, Gosu::Color::from_hsv(0, 0, 0.102));
				graphics().draw_rect(880, 580, 160, 50, Gosu::Color::from_hsv(0, 0, 0.102), -2);
				graphics().draw_rect(882, 583, 156, 45, Gosu::Color::from_hsv(0, 0, 0.306), -2);
			}
		}
		else if (pause) {
		grass.draw(-24.0 + grass_x, -23.0 + grass_y, -10);

		titlescreen.draw(900, 300);

		Gosu::Font font_titlescreen(100, "m5x7");

		font_titlescreen.draw_text_rel("Pause", 960, 100, 0, 0.5, 0.5, 1.0, 1.0, Gosu::Color::from_hsv(0, 0, 0.102));

		Gosu::Font font_start(30, "m5x7");

		if (input().mouse_x() > 882 && input().mouse_x() < 1038 && input().mouse_y() > 522 && input().mouse_y() < 568) {
			font_start.draw_text_rel("Continue", 960, 545, 0, 0.5, 0.5, 1.0, 1.0, Gosu::Color::from_hsv(0, 0, 0.306));
			graphics().draw_rect(880, 520, 160, 50, Gosu::Color::from_hsv(0, 0, 0.306), -2);
			graphics().draw_rect(882, 522, 156, 46, Gosu::Color::from_hsv(0, 0, 0.102), -2);
		}
		else {
			font_start.draw_text_rel("Continue", 960, 545, 0, 0.5, 0.5, 1.0, 1.0, Gosu::Color::from_hsv(0, 0, 0.102));
			graphics().draw_rect(880, 520, 160, 50, Gosu::Color::from_hsv(0, 0, 0.102), -2);
			graphics().draw_rect(882, 522, 156, 46, Gosu::Color::from_hsv(0, 0, 0.306), -2);
		}

		if (input().mouse_x() > 882 && input().mouse_x() < 1038 && input().mouse_y() > 582 && input().mouse_y() < 628) {
			font_start.draw_text_rel("Exit", 960, 605, 0, 0.5, 0.5, 1.0, 1.0, Gosu::Color::from_hsv(0, 0, 0.306));
			graphics().draw_rect(880, 580, 160, 50, Gosu::Color::from_hsv(0, 0, 0.306), -2);
			graphics().draw_rect(882, 583, 156, 45, Gosu::Color::from_hsv(0, 0, 0.102), -2);
		}
		else {
			font_start.draw_text_rel("Exit", 960, 605, 0, 0.5, 0.5, 1.0, 1.0, Gosu::Color::from_hsv(0, 0, 0.102));
			graphics().draw_rect(880, 580, 160, 50, Gosu::Color::from_hsv(0, 0, 0.102), -2);
			graphics().draw_rect(882, 583, 156, 45, Gosu::Color::from_hsv(0, 0, 0.306), -2);
		}
}
	}


	int frame_counter = 0;
	string current_directionY = "Down";
	string current_directionX = "Right";
	string current_state = "Walk_";

	bool startButtonLastFrame = false;

	bool attack = false;
	bool super_attack = false;
	int attack_state = 0;
	double speed = 1.2;

	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		try {
			if (attack) {
				if (frame_counter % 3 == 0)
					attack_state++;

				if (attack_state == 1)
					walk_anim = Gosu::Image(current_state + "1.png");
				else if (attack_state == 2)
					walk_anim = Gosu::Image(current_state + "2.png");
				else if (attack_state == 3)
					walk_anim = Gosu::Image(current_state + "3.png");
				else if (attack_state == 4)
					walk_anim = Gosu::Image(current_state + "4.png");
				else if (attack_state == 5)
					attack = false;
			}
			else if (super_attack) {
				if (frame_counter % 3 == 0)
					attack_state++;
				
				if (attack_state == 1)
					walk_anim = Gosu::Image("SuperAttack1.png");
				else if (attack_state == 2)
					walk_anim = Gosu::Image("SuperAttack2.png");
				else if (attack_state == 3)
					walk_anim = Gosu::Image("SuperAttack3.png");
				else if (attack_state == 4)
					walk_anim = Gosu::Image("SuperAttack4.png");
				else if (attack_state == 5)
					walk_anim = Gosu::Image("SuperAttack5.png");
				else if (attack_state == 6)
					walk_anim = Gosu::Image("SuperAttack6.png");
				else if (attack_state == 7)
					walk_anim = Gosu::Image("SuperAttack7.png");
				else if (attack_state == 8)
					walk_anim = Gosu::Image("SuperAttack8.png");
				else if (attack_state == 9)
					walk_anim = Gosu::Image("SuperAttack9.png");
				else if (attack_state == 10)
					walk_anim = Gosu::Image("SuperAttack10.png");
				else if (attack_state == 11)
					walk_anim = Gosu::Image("SuperAttack11.png");
				else if (attack_state == 12)
					super_attack = false;
			}
			else {
				if ((int)(frame_counter * 1.5) % 60 > 45 && current_state.find("Walk") != string::npos)
					walk_anim = Gosu::Image(current_state + current_directionY + current_directionX + "3.png");
				else if ((int)(frame_counter * 1.5) % 60 > 30 && current_state.find("Walk") != string::npos)
					walk_anim = Gosu::Image(current_state + current_directionY + current_directionX + "1.png");
				else if ((int)(frame_counter * 1.5) % 60 > 15 && current_state.find("Walk") != string::npos)
					walk_anim = Gosu::Image(current_state + current_directionY + current_directionX + "2.png");
				else if ((int)(frame_counter * 1.5) % 60 > 0)
					walk_anim = Gosu::Image(current_state + current_directionY + current_directionX + "1.png");
			}
		}
		catch (exception) {}

		if (lives == 0) {
			game_over = true;
			enemies.clear();
		}

		if (!game_over && game_start && !pause) {
			if (rand() % 100 < 5) {
				enemies.push_back(enemy(rand() % 1920, (rand() % 2) * 1080, 1));
			}

			if (rand() % 100 > 95) {
				enemies.push_back(enemy(((rand() % 2) * 1920), rand() % 1080, 1));
			}

			frame_counter = (frame_counter + 1) % 60;

			hit_counter++;

			if (input().down(Gosu::KB_ESCAPE) || (input().down(Gosu::GP_BUTTON_6) && !startButtonLastFrame)) {
				pause = true;
				startButtonLastFrame = true;
			}

			if (hit_counter >= 30) {
				hit = false;
			}

			if (frame_counter == 0) {
				
			}

			if ((input().down(Gosu::KB_LEFT_SHIFT) || input().down(Gosu::GP_BUTTON_9)) && stamina_meter >= 1.0) {
				speed = 2.0;
				stamina_meter = stamina_meter - 1.0;
			}
			else {
				speed = 1.2;
				stamina_meter = min(stamina_meter + 0.25, 300.0);
			}

			if ((input().down(Gosu::KB_SPACE) || input().down(Gosu::GP_BUTTON_10)) && attack_meter == 100) {
				attack_meter = 0;
				super_attack = true;
				attack_state = 0;
			}

			if ((input().down(Gosu::KB_W) || input().axis(Gosu::Button(Gosu::GP_LEFT_STICK_Y_AXIS)) < -0.5) && (input().down(Gosu::KB_A) || input().axis(Gosu::Button(Gosu::GP_LEFT_STICK_X_AXIS)) < -0.5) && !attack && !super_attack) {
				current_directionY = "Up";
				current_directionX = "Left";
				current_state = "Walk_";

				grass_y = fmod(grass_y + speed / sqrt(2.0), 16.0);
				grass_x = fmod(grass_x + speed / sqrt(2.0), 22.0);
				for (size_t i = 0; i < enemies.size(); i++) {
					enemies.at(i).y = enemies.at(i).y + speed / sqrt(2.0);
					enemies.at(i).x = enemies.at(i).x + speed / sqrt(2.0);
				}
			}
			else if ((input().down(Gosu::KB_W) || input().axis(Gosu::Button(Gosu::GP_LEFT_STICK_Y_AXIS)) < -0.5) && (input().down(Gosu::KB_D) || input().axis(Gosu::Button(Gosu::GP_LEFT_STICK_X_AXIS)) > 0.5) && !attack && !super_attack) {
				current_directionY = "Up";
				current_directionX = "Right";
				current_state = "Walk_";

				grass_y = fmod(grass_y + speed / sqrt(2.0), 16.0);
				grass_x = fmod(grass_x - speed / sqrt(2.0), 22.0);
				for (size_t i = 0; i < enemies.size(); i++) {
					enemies.at(i).y = enemies.at(i).y + speed / sqrt(2.0);
					enemies.at(i).x = enemies.at(i).x - speed / sqrt(2.0);
				}
			}
			else if ((input().down(Gosu::KB_S) || input().axis(Gosu::Button(Gosu::GP_LEFT_STICK_Y_AXIS)) > 0.5) && (input().down(Gosu::KB_A) || input().axis(Gosu::Button(Gosu::GP_LEFT_STICK_X_AXIS)) < -0.5) && !attack && !super_attack) {
				current_directionY = "Down";
				current_directionX = "Left";
				current_state = "Walk_";

				grass_y = fmod(grass_y - speed / sqrt(2.0), 16.0);
				grass_x = fmod(grass_x + speed / sqrt(2.0), 22.0);
				for (size_t i = 0; i < enemies.size(); i++) {
					enemies.at(i).y = enemies.at(i).y - speed / sqrt(2.0);
					enemies.at(i).x = enemies.at(i).x + speed / sqrt(2.0);
				}
			}
			else if ((input().down(Gosu::KB_S) || input().axis(Gosu::Button(Gosu::GP_LEFT_STICK_Y_AXIS)) > 0.5) && (input().down(Gosu::KB_D) || input().axis(Gosu::Button(Gosu::GP_LEFT_STICK_X_AXIS)) > 0.5) && !attack && !super_attack) {
				current_directionY = "Down";
				current_directionX = "Right";
				current_state = "Walk_";

				grass_y = fmod(grass_y - speed / sqrt(2.0), 16.0);
				grass_x = fmod(grass_x - speed / sqrt(2.0), 22.0);
				for (size_t i = 0; i < enemies.size(); i++) {
					enemies.at(i).y = enemies.at(i).y - speed / sqrt(2.0);
					enemies.at(i).x = enemies.at(i).x - speed / sqrt(2.0);
				}
			}
			else if ((input().down(Gosu::KB_W) || input().axis(Gosu::Button(Gosu::GP_LEFT_STICK_Y_AXIS)) < -0.5) && !attack && !super_attack) {
				current_directionY = "Up";
				current_state = "Walk_";

				grass_y = fmod(grass_y + speed, 16.0);
				for (size_t i = 0; i < enemies.size(); i++) {
					enemies.at(i).y = enemies.at(i).y + speed;
				}
			}
			else if ((input().down(Gosu::KB_S) || input().axis(Gosu::Button(Gosu::GP_LEFT_STICK_Y_AXIS)) > 0.5) && !attack && !super_attack) {
				current_directionY = "Down";
				current_state = "Walk_";

				grass_y = fmod(grass_y - speed, 16.0);
				for (size_t i = 0; i < enemies.size(); i++) {
					enemies.at(i).y = enemies.at(i).y - speed;
				}
			}
			else if ((input().down(Gosu::KB_A) || input().axis(Gosu::Button(Gosu::GP_LEFT_STICK_X_AXIS)) < -0.5) && !attack && !super_attack) {
				current_directionX = "Left";
				current_state = "Walk_";

				grass_x = fmod(grass_x + speed, 22.0);
				for (size_t i = 0; i < enemies.size(); i++) {
					enemies.at(i).x = enemies.at(i).x + speed;
				}
			}
			else if ((input().down(Gosu::KB_D) || input().axis(Gosu::Button(Gosu::GP_LEFT_STICK_X_AXIS)) > 0.5) && !attack && !super_attack) {
				current_directionX = "Right";
				current_state = "Walk_";

				grass_x = fmod(grass_x - speed, 22.0);
				for (size_t i = 0; i < enemies.size(); i++) {
					enemies.at(i).x = enemies.at(i).x - speed;
				}
			}
			else if (!attack && !super_attack)
				current_state = "Idle_";

			if ((input().down(Gosu::KB_LEFT) || input().down(Gosu::GP_BUTTON_2)) && !attack && !super_attack) {
				current_state = "Attack_UpLeft";
				current_directionX = "Left";
				current_directionY = "Up";
				attack = true;
				attack_state = 0;
			}
			else if ((input().down(Gosu::KB_RIGHT) || input().down(Gosu::GP_BUTTON_1)) && !attack && !super_attack) {
				current_state = "Attack_DownRight";
				current_directionX = "Right";
				current_directionY = "Down";
				attack = true;
				attack_state = 0;
			}
			else if ((input().down(Gosu::KB_UP) || input().down(Gosu::GP_BUTTON_3)) && !attack && !super_attack) {
				current_state = "Attack_UpRight";
				current_directionX = "Right";
				current_directionY = "Up";
				attack = true;
				attack_state = 0;

			}
			else if ((input().down(Gosu::KB_DOWN) || input().down(Gosu::GP_BUTTON_0)) && !attack && !super_attack) {
				current_state = "Attack_DownLeft";
				current_directionX = "Left";
				current_directionY = "Down";
				attack = true;
				attack_state = 0;
			}

			if (hit && current_state.find("Hurt") == string::npos && !super_attack)
				current_state = "Hurt" + current_state;

			for (size_t i = 0; i < enemies.size(); i++) {
				float delta_x = enemies.at(i).x - 960.0 +10.0;
				float delta_y = enemies.at(i).y - 540.0 +10.0;
				float new_delta_x = delta_x - delta_x / sqrt(delta_x * delta_x + delta_y * delta_y);
				float new_delta_y = delta_y - delta_y / sqrt(delta_x * delta_x + delta_y * delta_y);
				enemies.at(i).x = 960.0 + new_delta_x - 10.0;
				enemies.at(i).y = 540.0 + new_delta_y -10.0;

				if (frame_counter % 10 == 0) {
					enemies.at(i).walk_count = (enemies.at(i).walk_count + 1) % 4;
				}

				if (enemies.at(i).x > 960.0 - 10.0 - 10.0 && enemies.at(i).x < 960.0 + 10.0 - 10.0 && enemies.at(i).y > 540 - 10.0 - 10.0 && enemies.at(i).y < 540.0 + 10.0 - 10.0 && !hit && !super_attack) {
					enemies.erase(enemies.begin() + i);
					lives--;
					hit = true;
					hit_counter = 0;
				}

				if (attack) {
					if (current_directionX == "Right" && current_directionY == "Down" &&
						enemies.at(i).x > 940.0 && enemies.at(i).y > 520.0 && sqrt(delta_x * delta_x + delta_y * delta_y) < 30.0) {
						enemies.erase(enemies.begin() + i);
						points++;
						attack_meter = min(attack_meter + 1, 100);
					}
					if (current_directionX == "Left" && current_directionY == "Down" &&
						enemies.at(i).x < 960.0 && enemies.at(i).y > 520.0 && sqrt(delta_x * delta_x + delta_y * delta_y) < 30.0) {
						enemies.erase(enemies.begin() + i);
						points++;
						attack_meter = min(attack_meter + 1, 100);
					}
					if (current_directionX == "Right" && current_directionY == "Up" &&
						enemies.at(i).x > 940.0 && enemies.at(i).y < 540.0 && sqrt(delta_x * delta_x + delta_y * delta_y) < 30.0) {
						enemies.erase(enemies.begin() + i);
						points++;
						attack_meter = min(attack_meter + 1, 100);
					}
					if (current_directionX == "Left" && current_directionY == "Up" &&
						enemies.at(i).x < 960.0 && enemies.at(i).y < 540.0 && sqrt(delta_x * delta_x + delta_y * delta_y) < 30.0) {
						enemies.erase(enemies.begin() + i);
						points++;
						attack_meter = min(attack_meter + 1, 100);
					}
				}

				if (super_attack && sqrt(delta_x * delta_x + delta_y * delta_y) < 40.0) {
					enemies.erase(enemies.begin() + i);
					points++;
					attack_meter = min(attack_meter + 1, 100);
				}
			}
		}

		if (game_over) {
			if ((input().down(Gosu::MS_LEFT) && input().mouse_x() > 882 && input().mouse_x() < 1038 && input().mouse_y() > 522 && input().mouse_y() < 568) || input().down(Gosu::GP_BUTTON_6)) {
				game_over = false;
				lives = 6;
				stamina_meter = 300.0;
				attack_meter = 0;
				points = 0;
				hit = false;
			}

			if ((input().down(Gosu::MS_LEFT) && input().mouse_x() > 882 && input().mouse_x() < 1038 && input().mouse_y() > 582 && input().mouse_y() < 628) || input().down(Gosu::GP_BUTTON_4)) {
				PostMessage(GetActiveWindow(), WM_CLOSE, 0, 0);
			}
		}

		if (!game_start) {
			if ((input().down(Gosu::MS_LEFT) && input().mouse_x() > 882 && input().mouse_x() < 1038 && input().mouse_y() > 522 && input().mouse_y() < 568) || input().down(Gosu::GP_BUTTON_6)) {
				game_over = false;
				lives = 6;
				stamina_meter = 300.0;
				attack_meter = 0;
				points = 0;
				hit = false;
				game_start = true;
			}

			if ((input().down(Gosu::MS_LEFT) && input().mouse_x() > 882 && input().mouse_x() < 1038 && input().mouse_y() > 582 && input().mouse_y() < 628) || input().down(Gosu::GP_BUTTON_4)) {
				PostMessage(GetActiveWindow(), WM_CLOSE, 0, 0);
			}
		}

		if (pause) {
			if ((input().down(Gosu::MS_LEFT) && input().mouse_x() > 882 && input().mouse_x() < 1038 && input().mouse_y() > 522 && input().mouse_y() < 568) || (input().down(Gosu::GP_BUTTON_6) && !startButtonLastFrame)) {
				pause = false;
			}

			if ((input().down(Gosu::MS_LEFT) && input().mouse_x() > 882 && input().mouse_x() < 1038 && input().mouse_y() > 582 && input().mouse_y() < 628) || input().down(Gosu::GP_BUTTON_4)) {
				PostMessage(GetActiveWindow(), WM_CLOSE, 0, 0);
			}
		}

		if (input().down(Gosu::GP_BUTTON_6))
			startButtonLastFrame = true;
		else
			startButtonLastFrame = false;
	}
};

// C++ Hauptprogramm
int main()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	GameWindow window;
	window.show();
}
