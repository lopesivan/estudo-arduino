enum ButtonStates { UP, DOWN, PRESS, RELEASE };

enum ButtonStates delay_debounce (enum ButtonStates button_state)
{
    if (read_button())                       /* if pressed     */
    {
        if (button_state == PRESS)
        {
            button_state = DOWN;
        }
        if (button_state == UP)
        {
            _delay_ms (5);
            if (read_button() == 1)
            {
                button_state = PRESS;
            }
        }
    }
    else                                     /* if not pressed */
    {
        if (button_state == RELEASE)
        {
            button_state = UP;
        }
        if (button_state == DOWN)
        {
            if (read_button() == 0)
            {
                _delay_ms (5);
                if (read_button() == 0)
                {
                    button_state = RELEASE;
                }
            }
        }
    }
    return button_state;
}

