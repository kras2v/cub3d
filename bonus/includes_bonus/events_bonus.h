/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvalerii <kvalerii@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:34:24 by kvalerii          #+#    #+#             */
/*   Updated: 2025/07/23 16:31:48 by kvalerii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_BONUS_H
# define EVENTS_BONUS_H

typedef enum e_keys_events
{
	ON_KEYDOWN		= 2, // KeyPress
	ON_KEYUP		= 3, // KeyRelease
	ON_MOUSEDOWN	= 4, // ButtonPress
	ON_MOUSEUP		= 5, // ButtonRelease
	ON_MOUSEMOVE	= 6, // MotionNotify
	ON_ENTER		= 7, // EnterNotify
	ON_LEAVE		= 8, // LeaveNotify
	ON_FOCUSIN		= 9, // FocusIn
	ON_FOCUSOUT		= 10,// FocusOut
	ON_KEYMAP		= 11,// KeymapNotify
	ON_EXPOSE		= 12,// Expose
	ON_DESTROY		= 17,// DestroyNotify
	ON_RESIZE		= 25,// ResizeRequest
	ON_CLIENT_MSG	= 33,// ClientMessage
	ON_GENERIC		= 35 // GenericEvent
}	t_keys_events;

typedef enum e_event_mask
{
	NO_EVENT_MASK			= 0L,
	KEY_PRESS_MASK			= (1L << 0),
	KEY_RELEASE_MASK		= (1L << 1),
	BUTTON_PRESS_MASK		= (1L << 2),
	BUTTON_RELEASE_MASK		= (1L << 3),
	POINTER_MOTION_MASK		= (1L << 6),
	EXPOSURE_MASK			= (1L << 15),
	STRUCTURE_NOTIFY_MASK	= (1L << 17)
}	t_event_mask;

#endif