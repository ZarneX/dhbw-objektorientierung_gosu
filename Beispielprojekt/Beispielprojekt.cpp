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
		: Window(800, 600)
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

	{
		set_caption("Gosu Tutorial mit Git");
	}

	Gosu::Image up_right1;// = Gosu::Image("Walk_UpRight1");
	Gosu::Image up_right2;// = Gosu::Image("Walk_UpRight2");
	Gosu::Image up_right3;// = Gosu::Image("Walk_UpRight3");
	Gosu::Image up_left1; //= Gosu::Image("Walk_UpLeft1");
	Gosu::Image up_left2; //= Gosu::Image("Walk_UpLeft2");
	Gosu::Image up_left3; //= Gosu::Image("Walk_UpLeft3");
	Gosu::Image down_right1;// = Gosu::Image("Walk_DownRight1");
	Gosu::Image down_right2;// = Gosu::Image("Walk_DownRight2");
	Gosu::Image down_right3;// = Gosu::Image("Walk_DownRight3");
	Gosu::Image down_left1;// = Gosu::Image("Walk_DownLeft1");
	Gosu::Image down_left2;// = Gosu::Image("Walk_DownLeft2");
	Gosu::Image down_left3;// = Gosu::Image("Walk_DownLeft3");

	struct enemy
	{
	public: 
		float x;
		float y;
		int walk_count;
	};

	struct shot
	{
		float start_x;
		float end_x;
		float start_y;
		float end_y;
	};

	vector<enemy> enemies;
	int points = 0;
	int lives = 6;
	bool hit = false;
	int hit_counter = 0;
	bool game_over = false;
	bool game_start = false;

	Gosu::Image walk_anim;

	// Wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{
		if (!game_over && game_start) {

			walk_anim.draw(385, 285, 2);

			Gosu::Font font(20);
			font.draw_text("Points: " + to_string(points), 5, 5, 0);
			font.draw_text("Lives: ", 695, 5, 0);

			if (lives >= 1)
				graphics().draw_rect(750, 10, 5, 10, Gosu::Color::WHITE, 0);

			if (lives >= 2)
				graphics().draw_rect(755, 10, 5, 10, Gosu::Color::WHITE, 0);

			if (lives >= 3)
				graphics().draw_rect(765, 10, 5, 10, Gosu::Color::WHITE, 0);

			if (lives >= 4)
				graphics().draw_rect(770, 10, 5, 10, Gosu::Color::WHITE, 0);

			if (lives >= 5)
				graphics().draw_rect(780, 10, 5, 10, Gosu::Color::WHITE, 0);

			if (lives >= 6)
				graphics().draw_rect(785, 10, 5, 10, Gosu::Color::WHITE, 0);

			for (size_t i = 0; i < enemies.size(); i++) {

				if (enemies.at(i).walk_count == 0) {
					if (enemies.at(i).x <= 400 && enemies.at(i).y >= 300)
						up_right1.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x <= 400 && enemies.at(i).y < 300)
						down_right1.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x > 400 && enemies.at(i).y < 300)
						down_left1.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x > 400 && enemies.at(i).y >= 300)
						up_left1.draw(enemies.at(i).x, enemies.at(i).y, 1);
				}
				else if (enemies.at(i).walk_count == 1) {
					if (enemies.at(i).x <= 400 && enemies.at(i).y >= 300)
						up_right2.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x <= 400 && enemies.at(i).y < 300)
						down_right2.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x > 400 && enemies.at(i).y < 300)
						down_left2.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x > 400 && enemies.at(i).y >= 300)
						up_left2.draw(enemies.at(i).x, enemies.at(i).y, 1);
				}
				else if (enemies.at(i).walk_count == 2) {
					if (enemies.at(i).x <= 400 && enemies.at(i).y >= 300)
						up_right1.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x <= 400 && enemies.at(i).y < 300)
						down_right1.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x > 400 && enemies.at(i).y < 300)
						down_left1.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x > 400 && enemies.at(i).y >= 300)
						up_left1.draw(enemies.at(i).x, enemies.at(i).y, 1);
				}
				else if (enemies.at(i).walk_count == 3) {
					if (enemies.at(i).x <= 400 && enemies.at(i).y >= 300)
						up_right3.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x <= 400 && enemies.at(i).y < 300)
						down_right3.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x > 400 && enemies.at(i).y < 300)
						down_left3.draw(enemies.at(i).x, enemies.at(i).y, 1);
					else if (enemies.at(i).x > 400 && enemies.at(i).y >= 300)
						up_left3.draw(enemies.at(i).x, enemies.at(i).y, 1);
				}
			}

			if (input().down(Gosu::KB_LEFT)) {
				graphics().draw_line(400, 300, Gosu::Color::WHITE, 370, 330, Gosu::Color::WHITE, 0);
			}
			else if (input().down(Gosu::KB_RIGHT)) {
				graphics().draw_line(400, 300, Gosu::Color::WHITE, 430, 270, Gosu::Color::WHITE, 0);
			}
			else if (input().down(Gosu::KB_UP)) {
				graphics().draw_line(400, 300, Gosu::Color::WHITE, 370, 270, Gosu::Color::WHITE, 0);
			}
			else if (input().down(Gosu::KB_DOWN)) {
				graphics().draw_line(400, 300, Gosu::Color::WHITE, 430, 330, Gosu::Color::WHITE, 0);
			}
		}
		else if (game_over) {
			Gosu::Font font(50);
			font.draw_text_rel("Game Over", 400, 200, 0, 0.5, 0.5);

			Gosu::Font font_retry(30);

			font_retry.draw_text_rel("Points: " + to_string(points), 400, 250, 0, 0.5, 0.5, 1.0, 1.0, Gosu::Color::WHITE);

			if (input().mouse_x() > 352 && input().mouse_x() < 448 && input().mouse_y() > 282 && input().mouse_y() < 328) {
				font_retry.draw_text_rel("Retry", 400, 305, 0, 0.5, 0.5, 1.0, 1.0, Gosu::Color::BLACK);
				graphics().draw_rect(350, 280, 100, 50, Gosu::Color::BLACK, -2);
				graphics().draw_rect(352, 282, 96, 46, Gosu::Color::WHITE, -2);
			}
			else {
				font_retry.draw_text_rel("Retry", 400, 305, 0, 0.5, 0.5, 1.0, 1.0, Gosu::Color::WHITE);
				graphics().draw_rect(350, 280, 100, 50, Gosu::Color::WHITE, -2);
				graphics().draw_rect(352, 282, 96, 46, Gosu::Color::BLACK, -2);
			}

		}
		else if (!game_start) {
			Gosu::Font font_start(30);

			if (input().mouse_x() > 322 && input().mouse_x() < 478 && input().mouse_y() > 282 && input().mouse_y() < 328) {
				font_start.draw_text_rel("Start Game", 400, 305, 0, 0.5, 0.5, 1.0, 1.0, Gosu::Color::BLACK);
				graphics().draw_rect(320, 280, 160, 50, Gosu::Color::BLACK, -2);
				graphics().draw_rect(322, 282, 156, 46, Gosu::Color::WHITE, -2);
			}
			else {
				font_start.draw_text_rel("Start Game", 400, 305, 0, 0.5, 0.5, 1.0, 1.0, Gosu::Color::WHITE);
				graphics().draw_rect(320, 280, 160, 50, Gosu::Color::WHITE, -2);
				graphics().draw_rect(322, 282, 156, 46, Gosu::Color::BLACK, -2);
			}
		}
	}


	int frame_counter = 0;
	string current_directionY = "Down";
	string current_directionX = "Right";
	string current_state = "Walk_";
	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		if ((int)(frame_counter * 1.5) % 60 > 45 && current_state.find("Walk") != string::npos)
			walk_anim = Gosu::Image(current_state + current_directionY + current_directionX + "3.png");
		else if ((int)(frame_counter * 1.5) % 60 > 30 && current_state.find("Walk") != string::npos)
			walk_anim = Gosu::Image(current_state + current_directionY + current_directionX + "1.png");
		else if ((int)(frame_counter * 1.5) % 60 > 15 && current_state.find("Walk") != string::npos)
			walk_anim = Gosu::Image(current_state + current_directionY + current_directionX + "2.png");
		else if ((int)(frame_counter * 1.5) % 60 > 0)
			walk_anim = Gosu::Image(current_state + current_directionY + current_directionX + "1.png");

		if (lives == 0) {
			game_over = true;
			enemies.clear();
		}

		if (!game_over && game_start) {
			if (rand() % 100 < 5) {
				enemies.push_back(enemy(rand() % 800, (rand() % 2) * 597, 1));
			}

			if (rand() % 100 > 95) {
				enemies.push_back(enemy(((rand() % 2) * 797), rand() % 600, 1));
			}

			frame_counter = (frame_counter + 1) % 60;

			hit_counter++;

			if (hit_counter >= 30) {
				hit = false;
			}

			if (frame_counter == 0) {
				
			}

			if (input().down(Gosu::KB_W) && input().down(Gosu::KB_A)) {
				current_directionY = "Up";
				current_directionX = "Left";
				current_state = "Walk_";
				for (size_t i = 0; i < enemies.size(); i++) {
					enemies.at(i).y = enemies.at(i).y + 1.2 / sqrt(2.0);
					enemies.at(i).x = enemies.at(i).x + 1.2 / sqrt(2.0);
				}
			}
			else if (input().down(Gosu::KB_W) && input().down(Gosu::KB_D)) {
				current_directionY = "Up";
				current_directionX = "Right";
				current_state = "Walk_";
				for (size_t i = 0; i < enemies.size(); i++) {
					enemies.at(i).y = enemies.at(i).y + 1.2 / sqrt(2.0);
					enemies.at(i).x = enemies.at(i).x - 1.2 / sqrt(2.0);
				}
			}
			else if (input().down(Gosu::KB_S) && input().down(Gosu::KB_A)) {
				current_directionY = "Down";
				current_directionX = "Left";
				current_state = "Walk_";
				for (size_t i = 0; i < enemies.size(); i++) {
					enemies.at(i).y = enemies.at(i).y - 1.2 / sqrt(2.0);
					enemies.at(i).x = enemies.at(i).x + 1.2 / sqrt(2.0);
				}
			}
			else if (input().down(Gosu::KB_S) && input().down(Gosu::KB_D)) {
				current_directionY = "Down";
				current_directionX = "Right";
				current_state = "Walk_";
				for (size_t i = 0; i < enemies.size(); i++) {
					enemies.at(i).y = enemies.at(i).y - 1.2 / sqrt(2.0);
					enemies.at(i).x = enemies.at(i).x - 1.2 / sqrt(2.0);
				}
			}
			else if (input().down(Gosu::KB_W)) {
				current_directionY = "Up";
				current_state = "Walk_";
				for (size_t i = 0; i < enemies.size(); i++) {
					enemies.at(i).y = enemies.at(i).y + 1.2;
				}
			}
			else if (input().down(Gosu::KB_S)) {
				current_directionY = "Down";
				current_state = "Walk_";
				for (size_t i = 0; i < enemies.size(); i++) {
					enemies.at(i).y = enemies.at(i).y - 1.2;
				}
			}
			else if (input().down(Gosu::KB_A)) {
				current_directionX = "Left";
				current_state = "Walk_";
				for (size_t i = 0; i < enemies.size(); i++) {
					enemies.at(i).x = enemies.at(i).x + 1.2;
				}
			}
			else if (input().down(Gosu::KB_D)) {
				current_directionX = "Right";
				current_state = "Walk_";
				for (size_t i = 0; i < enemies.size(); i++) {
					enemies.at(i).x = enemies.at(i).x - 1.2;
				}
			}
			else
				current_state = "Idle_";

			if (hit)
				current_state = "Hurt" + current_state;

			for (size_t i = 0; i < enemies.size(); i++) {
				float delta_x = enemies.at(i).x - 400.0 + 2.5;
				float delta_y = enemies.at(i).y - 300.0 + 2.5;
				delta_x = delta_x - delta_x / sqrt(delta_x * delta_x + delta_y * delta_y);
				delta_y = delta_y - delta_y / sqrt(delta_x * delta_x + delta_y * delta_y);
				enemies.at(i).x = 400.0 + delta_x - 2.5;
				enemies.at(i).y = 300.0 + delta_y - 2.5;

				if (frame_counter % 10 == 0) {
					enemies.at(i).walk_count = (enemies.at(i).walk_count + 1) % 4;
				}

				if (enemies.at(i).x > 400.0 - 2.5 && enemies.at(i).x < 400.0 + 2.5 && enemies.at(i).y > 300.0 - 2.5 && enemies.at(i).y < 300.0 + 2.5 && hit == false) {
					enemies.erase(enemies.begin() + i);
					lives--;
					hit = true;
					hit_counter = 0;
				}
			}
		}

		if (game_over) {
			if (input().down(Gosu::MS_LEFT) && input().mouse_x() > 352 && input().mouse_x() < 448 && input().mouse_y() > 282 && input().mouse_y() < 328) {
				game_over = false;
				lives = 6;
				points = 0;
				hit = false;
			}
		}

		if (!game_start) {
			if (input().down(Gosu::MS_LEFT) && input().mouse_x() > 322 && input().mouse_x() < 478 && input().mouse_y() > 282 && input().mouse_y() < 328) {
				game_over = false;
				lives = 6;
				points = 0;
				hit = false;
				game_start = true;
			}
		}
	}
};

// C++ Hauptprogramm
int main()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	GameWindow window;
	window.show();
}
