Object subclass: Ride [
    | rideID pickup dropoff distance |

    Ride class >> newWith: id pickup: p dropoff: d distance: dist [
        ^self new
            rideID: id;
            pickup: p;
            dropoff: d;
            distance: dist
    ]

    rideID: id [ rideID := id ]
    pickup: p [ pickup := p ]
    dropoff: d [ dropoff := d ]
    distance: dist [ distance := dist ]

    fare [ ^distance * 2.5 ]

    printDetails [
        ('Ride ', rideID asString, ': from ', pickup, ' to ', dropoff, ' - Fare: $', self fare asString) displayNl
    ]
]

| ride |
ride := Ride newWith: 101 pickup: 'Home' dropoff: 'Work' distance: 12.
ride printDetails.
