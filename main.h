// check if edges overlap and collinear
bool checkOverlapCollinear(edge3D e1, edge3D e2) ;

// check edges collinear
bool checkCoplanar(edge3D e1, edge3D e2 , edge3D e3) ;

// check if plane hides an edge from direction
bool checkHidden(plane p , edge3D e , edge3D direction) ; // still trying to formulate the probelem
// HOW TO CHECK HIDDEN :
// first check both end points of edge lie on same side of plane substitute the take product and multiply result should be greater than 0
// take an obnoxiously large coordinate in the direction you want to see like if you are observing from +y direction put (0,INF,0) where INF is large number
// take a point and return if substitution product less than 0

