/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 14:57:53 by dkathlee          #+#    #+#             */
/*   Updated: 2019/12/04 12:55:14 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		zoom(int b, int x, int y, t_view *v)
{
	long double	deltax;
	long double	deltay;
	long double	perc_x;
	long double	perc_y;

	perc_x = (long double)x / WIDTH;
	perc_y = (long double)y / HEIGHT;
	deltax = (v->fract.r_end - v->fract.r_start) *
									(v->shift == true ? 0.1 : 0.01);
	deltay = (v->fract.i_end - v->fract.i_start) *
									(v->shift == true ? 0.1 : 0.01);
	if (b == BTN_MOUSE_SCROLL_UP || b == BTN_MOUSE_SCROLL_LEFT)
	{
		v->fract.r_start += deltax * perc_x * 2;
		v->fract.r_end -= deltax * (1.0 - perc_x) * 2;
		v->fract.i_start += deltay * perc_y * 2;
		v->fract.i_end -= deltay * (1.0 - perc_y) * 2;
	}
	else if (b == BTN_MOUSE_SCROLL_DOWN || b == BTN_MOUSE_SCROLL_RIGHT)
	{
		v->fract.r_start -= deltax * perc_x * 2;
		v->fract.r_end += deltax * (1.0 - perc_x) * 2;
		v->fract.i_start -= deltay * perc_y * 2;
		v->fract.i_end += deltay * (1.0 - perc_y) * 2;
	}
}

int				mouse_press(int b, int x, int y, t_view *v)
{
	if (v->help)
		return (1);
	zoom(b, x, y, v);
	if (b == BTN_MOUSE_LEFT && x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		v->mouse.is_pressed = true;
		v->mouse.x = x;
		v->mouse.y = y;
	}
	v->fract.p_width = (v->fract.r_end - v->fract.r_start) / WIDTH;
	v->fract.p_height = (v->fract.i_end - v->fract.i_start) / HEIGHT;
	draw_fractal(v);
	return (1);
}

int				mouse_release(int b, int x, int y, t_view *v)
{
	(void)x;
	(void)y;
	if (b == BTN_MOUSE_LEFT)
		v->mouse.is_pressed = false;
	return (1);
}

int				mouse_move(int x, int y, t_view *v)
{
	long double	dx;
	long double	dy;

	if (v->help)
		return (1);
	if ((!v->mouse.is_pressed && v->fract.type != fr_julia) || x < 0 ||
	x >= WIDTH || y < 0 || y >= HEIGHT || (x == v->mouse.x && y == v->mouse.y))
		return (1);
	v->mouse.prev_x = v->mouse.x;
	v->mouse.prev_y = v->mouse.y;
	v->mouse.x = x;
	v->mouse.y = y;
	if (v->mouse.is_pressed == true)
	{
		dx = (x - v->mouse.prev_x) * v->fract.p_height;
		dy = (y - v->mouse.prev_y) * v->fract.p_width;
		v->fract.r_start -= dx;
		v->fract.r_end -= dx;
		v->fract.i_start -= dy;
		v->fract.i_end -= dy;
	}
	draw_fractal(v);
	return (1);
}
