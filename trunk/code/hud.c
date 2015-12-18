#ifndef _HUD_C_
#define _HUD_C_

COLOR* hud_color(var angle)
{
	return vector(
		128 + 127 * sinv(angle),
		128 + 127 * sinv(angle + 120),
		128 + 127 * sinv(angle + 240));
}

void hud_render()
{
	var alpha = 50 + 50 * sinv(30 * total_ticks);
	
	COLOR col;
	var angle = 60 * total_ticks;
	
	//draw_textmode("Comic Sans", 2, 30, 100);
	
	// Render normal text
	draw_text("Current Level:", 20, 20, hud_color(angle + 0));
	draw_text("Letter Count:", 20, 50, hud_color(angle + 90));
	draw_text("Error Count:", 20, 80, hud_color(angle + 180));
	draw_text("Accuracy:", 20, 110, hud_color(angle + 270));
	draw_text("Popularity:", 20, 140, hud_color(angle + 360));
	
	//draw_textmode("Comic Sans", 2, 30, alpha);
	
	// Render blinking text
	draw_text(str_for_num(NULL, input_getLevel()), 150, 20, COLOR_WHITE);
	draw_text(str_for_num(NULL, input_getLetterCount()), 150, 50, COLOR_WHITE);
	draw_text(str_for_num(NULL, input_getErrorCount()), 150, 80, COLOR_WHITE);
	
	STRING *strTemp = "#64";
	str_for_num(strTemp, input_getAccuracy());
	str_cat(strTemp, "%");
	draw_text(strTemp, 150, 110, COLOR_WHITE);
	
	STRING *strTemp = "#64";
	str_for_num(strTemp, 10 * input_getPopularity());
	str_cat(strTemp, "%");
	draw_text(strTemp, 150, 140, COLOR_WHITE);
}

#endif // #ifndef _HUD_C_


