#include <stdio.h>

typedef enum Event_type_t
{
    FUEL_CONSUMPTION,
    LEAK,
    GAS_STATION,
    MECHANIC,
    GOAL
}Event_type_t;

typedef struct Event_t
{
    int distance;
    Event_type_t event_type;
    int event_val;
}Event_t;

float min_fuel_consumption(Event_t *Events, int n_events);

#define MAX_EVENTS 50
int main()
{
    char buffer[128];
    char dummy[32];

    Event_t Events[MAX_EVENTS];
    int ev_size = 0;

    int ev_distance;
    Event_type_t ev_t;
    int ev_val;

    while (1)
    {
        // Leggo la distanza dell'evento
        scanf("%d", &ev_distance);

        // Leggo il tipo di evento
        scanf("%s",buffer);

        if (buffer[0] == 'F')
        {
            // Fuel consumption
            // Leggo "consumption"
            scanf("%s",buffer);

            // Leggo il valore
            scanf("%d",&ev_val);

            if (ev_distance == 0 && ev_val == 0)
            {
                // Programma terminato
                break;
            }
            Events[ev_size].distance = ev_distance;
            Events[ev_size].event_val = ev_val;
            Events[ev_size].event_type = FUEL_CONSUMPTION;
            ev_size++;
        }
        else if (buffer[0] == 'L')
        {
            // Leak
            Events[ev_size].distance = ev_distance;
            Events[ev_size].event_val = ev_val;
            Events[ev_size].event_type = LEAK;
            ev_size++;
        }
        else if (buffer[0] == 'G' && buffer[1] == 'a')
        {
            // Gas station
            // Leggo "station"
            scanf("%s",dummy);
            Events[ev_size].distance = ev_distance;
            Events[ev_size].event_val = ev_val;
            Events[ev_size].event_type = GAS_STATION;
            ev_size++;
        }
        else if (buffer[0] == 'M')
        {
            // Mechanic
            Events[ev_size].distance = ev_distance;
            Events[ev_size].event_val = ev_val;
            Events[ev_size].event_type = MECHANIC;
            ev_size++;
        }
        else if (buffer[0] == 'G' && buffer[1] == 'o')
        {
            // Goal
            Events[ev_size].distance = ev_distance;
            Events[ev_size].event_val = ev_val;
            Events[ev_size].event_type = GOAL;
            ev_size++;

            float res = min_fuel_consumption(Events,ev_size);
            printf("%.3f\n",res);
            ev_size = 0;
        }
    }

}

float min_fuel_consumption(Event_t *Events, int n_events)
{
    float f_p_k = (float)(Events[0].event_val) / 100.f;
    int n_leaks = 0;

    float min_fuel_needed = 0;
    float current_fuel_needed = 0;

    for (int i = 1; i < n_events; i++)
    {
        current_fuel_needed = current_fuel_needed + (Events[i].distance-Events[i-1].distance) * (f_p_k + n_leaks);
        
        if (current_fuel_needed > min_fuel_needed)
            min_fuel_needed = current_fuel_needed;
        
        switch (Events[i].event_type)
        {
        case FUEL_CONSUMPTION:
            f_p_k = (float)(Events[i].event_val) / 100.f;
            break;
        case LEAK:
            n_leaks++;
            break;
        case GAS_STATION:
            current_fuel_needed = 0;
            break;
        case MECHANIC:
            n_leaks = 0;
            break;
        
        default:
            break;
        }
        
    }
    return min_fuel_needed;
}