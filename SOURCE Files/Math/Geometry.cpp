/**
 *   ////////////////////////
 *   // Maqsad Geometry template //
 *   ////////////////////////
 *
 * CONTENTS:
 *  - struct P (point)
 *  - struct L (canonical line with integer parameters)
 *  - left turn
 *  - point inside triangle
 *  - polar angle
 *  - point inside polygon
 *  - distance from a point to a line
 *  - distance from a point to a line segment
 *  - line intersection
 *  - line segment intersection
 *  - circle through 3 points
 *  - circle of a given radius through 2 points
 *  - cut polygon (cut a convex polygon by a half-plane)
 *  - triangle area from median lengths
 * 
  * Point *
 *********
 * A simple point class used by some of the routines below.
 * Anything else that supports .x and .y will work just as
 * well. There are 2 variants - double and int.
 **/
 #define aa first
 #define bb second
 #define FASTIO ios_base::sync_with_stdio(false);cin.tie(NULL); cout.tie(NULL);
 #define M_PI acos(-1)
 #define EPS 1e-9

struct P { double x, y; P() {}; P( double q, double w ) : x( q ), y( w ) {} };
//struct P { int x, y; P() {}; P( int q, int w ) : x( q ), y( w ) {} };

/********************************
 * Line with integer parameters *
 ********************************
 * Represents a line through two lattice points as an
 * implicit equation:
 *      ax + by = c
 * Stores a, b and c in lowest terms with a unique
 * representation (positive a; if a is 0, then positive b).
 * Create a line by giving either (a, b, c) or a pair
 * of points, p and q (p == q is ok, but expect a == b == 0).
 * Perfect for testing whether 3 or more points are collinear -
 * simply compute lines through all pairs of points and store
 * them in a set or a map (see UVA184).
 * REQUIRES:
 * struct P
 * from number.cpp: gcd(int, int)
 * FIELD TESTING:
 *      Passed UVA 184
 **/
struct L
{
    int a, b, c;

    // Params: A, B, C are raw line coefficients for Ax + By = C.
    void init( int A, int B, int C )
    {
        if( A < 0 || A == 0 && B < 0 ) { A = -A; B = -B; C = -C; }
        int d = A ?
            gcd( gcd( abs( A ), abs( B ) ), C ) :
            ( B || C ? gcd( abs( B ), C ) : 1 );
        a = A / d;
        b = B / d;
        c = C / d;
    }

    // constructors
    // Params: none.
    L() {}
    // Params: A, B, C are line coefficients.
    L( int A, int B, int C ) { init( A, B, C ); }
    // Params: p, q are two points defining the line.
    L( P p, P q ) { init( q.y - p.y, p.x - q.x, p.x * q.y - p.y * q.x ); }

    // Params: l is the line compared in lexicographic (a, b, c) order.
    bool operator<( const L &l ) const
    {
        return a < l.a || a == l.a && ( b < l.b || b == l.b && c < l.c );
    }
};

/************
 * Distance *
 ************
 * Computes the distance between two points a and b.
 * #include <math.h>
 **/
// Params: ax, ay and bx, by are endpoint coordinates of two points.
double dist( double ax, double ay, double bx, double by )
{
    return sqrt( ( ax - bx ) * ( ax - bx ) + ( ay - by ) * ( ay - by ) );
}

/********************
 * Squared distance *
 ********************
 * ... between two points.
 */
// Params: p and q are two points whose squared distance is returned.
__typeof( P().x ) dist2( P p, P q )
{
    return ( p.x - q.x ) * ( p.x - q.x ) + ( p.y - q.y ) * ( p.y - q.y );
}

/*************
 * Left turn *
 *************
 * Returns true iff the sequence v1->v2->v3 is a left turn in
 * the plane. Straight line is not a left turn (change to ">= -EPS").
 * #define EPS 1e-7
 **/
// Params: (x1,y1), (x2,y2), (x3,y3) are ordered points to test orientation.
bool leftTurn( double x1, double y1, double x2, double y2, double x3, double y3 )
{
    return ( x2 - x1 ) * ( y3 - y1 ) - ( y2 - y1 ) * ( x3 - x1 ) > EPS;
}

/*************
 * Left turn * (this one works with integers)
 *************
 * Returns true iff the sequence v1->v2->v3 is a left turn in
 * the plane. Straight line is not a left turn (change to ">= -C( EPS )").
 * #define EPS ... (1e-7 for doubles, 0 for ints)
 **/
template< class C >
// Params: (x1,y1), (x2,y2), (x3,y3) are generic numeric points to test orientation.
bool leftTurn( C x1, C y1, C x2, C y2, C x3, C y3 )
{
    return ( x2 - x1 ) * ( y3 - y1 ) - ( y2 - y1 ) * ( x3 - x1 ) > C( EPS );
}

/*************
 * Left turn * (for either of the two P (point) structs)
 *************
 * Returns true iff the sequence v1->v2->v3 is a left turn in
 * the plane. Straight line is not a left turn (change to ">= -C( EPS )").
 * #define EPS ...
 **/
// Params: a, b, c are points tested for left-turn orientation.
bool leftTurn( P a, P b, P c )
{
    return ( b.x - a.x ) * ( c.y - b.y ) - ( b.y - a.y ) * ( c.x - b.x ) > EPS;
}

/*************************
 * Point inside triangle *
 *************************
 * Returns true iff point (xx,yy) is inside the counter-clockwise
 * triangle (x[3],y[3])
 * REQUIRES: leftTurn()
 **/
// Params: x and y hold triangle vertices, xx and yy are the query point.
bool pointInsideTriangle( double x[], double y[], double xx, double yy )
{
    return leftTurn( x[0], y[0], x[1], y[1], xx, yy )
        && leftTurn( x[1], y[1], x[2], y[2], xx, yy )
        && leftTurn( x[2], y[2], x[0], y[0], xx, yy );
}

/***************
 * Polar angle *
 ***************
 * Returns an angle in the range [0, 2*Pi) of a given Cartesian point.
 * If the point is (0,0), -1.0 is returned.
 * REQUIRES:
 * #include <math.h>
 * #define EPS 0.000000001 // or your choice
 * P has members x and y.
 **/
// Params: p is the Cartesian point whose polar angle is computed.
double polarAngle( P p )
{
    if( fabs( p.x ) <= EPS && fabs( p.y ) <= EPS ) return -1.0;
    if( fabs( p.x ) <= EPS ) return ( p.y > EPS ? 1.0 : 3.0 ) * acos( 0 );
    double theta = atan( 1.0 * p.y / p.x );
    if( p.x > EPS ) return( p.y >= -EPS ? theta : ( 4 * acos( 0 ) + theta ) );
    return( 2 * acos( 0 ) + theta );
}

/************************
 * Point inside polygon *
 ************************
 * Returns true iff p is inside poly.
 * PRE: The vertices of poly are ordered (either clockwise or
 *      counter-clockwise.
 * POST: Modify code inside to handle the special case of "on an edge".
 * REQUIRES:
 * polarAngle()
 * #include <math.h>
 * #include <vector>
 * #define EPS 0.000000001 // or your choice
 **/
// Params: p is the query point and poly is the polygon vertex list.
bool pointInPoly( P p, vector< P > &poly )
{
    int n = poly.size();
    double ang = 0.0;
    for( int i = n - 1, j = 0; j < n; i = j++ )
    {
        P v( poly[i].x - p.x, poly[i].y - p.y );
        P w( poly[j].x - p.x, poly[j].y - p.y );
        double va = polarAngle( v );
        double wa = polarAngle( w );
        double xx = wa - va;
        if( va < -0.5 || wa < -0.5 || fabs( fabs( xx ) - 2 * acos( 0 ) ) < EPS )
        {
            // POINT IS ON THE EDGE
            assert( false );
            ang += 2 * acos( 0 );
            continue;
        }
        if( xx < -2 * acos( 0 ) ) ang += xx + 4 * acos( 0 );
        else if( xx > 2 * acos( 0 ) ) ang += xx - 4 * acos( 0 );
        else ang += xx;
    }
    return( ang * ang > 1.0 );
}

/***********************************
 * Distance from a point to a line *
 ***********************************
 * Returns the distance from p to the line defined by {a, b}.
 * The closest point on the line is returned through (cpx, cpy).
 * Does not work for degenerate lines (when answer is undefined).
 * REQUIRES:
 * #include <math.h>
 * #define EPS ...
 * dist()
 **/
// Params: a,b define a line; p is query point; cpx,cpy receive closest point.
double distToLine(
    double ax, double ay,
    double bx, double by,
    double px, double py,
    double *cpx, double *cpy )
{
    //Formula: cp = a + (p-a).(b-a) / |b-a| * (b-a)
    double proj = ( ( px - ax ) * ( bx - ax ) + ( py - ay ) * ( by - ay ) ) /
                  ( ( bx - ax ) * ( bx - ax ) + ( by - ay ) * ( by - ay ) );
    *cpx = ax + proj * ( bx - ax );
    *cpy = ay + proj * ( by - ay );
    return dist( px, py, *cpx, *cpy );
}

/*******************************************
 * Distance from a point to a line segment *
 *******************************************
 * Returns the distance from p to the line segment ab.
 * The closest point on ab is returned through (cpx, cpy).
 * Works correctly for degenerate line segments (a == b).
 * REQUIRES:
 * #include <math.h>
 * #define EPS ...
 * dist()
 * distToLine()
 **/
// Params: a,b define a segment; p is query point; cpx,cpy receive closest point.
double distToLineSegment(
    double ax, double ay,
    double bx, double by,
    double px, double py,
    double *cpx, double *cpy )
{
    if( ( bx - ax ) * ( px - ax ) + ( by - ay ) * ( py - ay ) < EPS )
    {
        *cpx = ax;
        *cpy = ay;
        return dist( ax, ay, px, py );
    }

    if( ( ax - bx ) * ( px - bx ) + ( ay - by ) * ( py - by ) < EPS )
    {
        *cpx = bx;
        *cpy = by;
        return dist( bx, by, px, py );
    }

    return distToLine( ax, ay, bx, by, px, py, cpx, cpy );
}

/*********************
 * Line intersection *
 *********************
 * Returns the point of intersection of two lines:
 * (x[0],y[0])-(x[1],y[1]) and (x[2],y[2])-(x[3],y[3]).
 * Puts the result (x, y) into (r[0], r[1]) and returns true.
 * If there is no intersection, return false;
 * USED BY: circle3pts
 * #include <math.h>
 * #define EPS ...
 **/
// Params: x,y store two lines by endpoints; r receives intersection point.
bool lineIntersect( double x[], double y[], double r[] )
{
    double n[2]; n[0] = y[3] - y[2]; n[1] = x[2] - x[3];
    double denom = n[0] * ( x[1] - x[0] ) + n[1] * ( y[1] - y[0] );
    if( fabs( denom ) < EPS ) return false;
    double num = n[0] * ( x[0] - x[2] ) + n[1] * ( y[0] - y[2] );
    double t = -num / denom;
    r[0] = x[0] + t * ( x[1] - x[0] );
    r[1] = y[0] + t * ( y[1] - y[0] );
    return true;
}

/*********************
 * Line intersection * (P version)
 *********************
 * Returns the point of intersection of two lines:
 * (x[0],y[0])-(x[1],y[1]) and (x[2],y[2])-(x[3],y[3]).
 * Puts the result (x, y) into (r[0], r[1]) and returns true.
 * If there is no intersection, return false;
 * #include <math.h>
 * #define EPS ...
 **/
// Params: a,b define first line; c,d second line; r receives intersection.
bool lineIntersect( P a, P b, P c, P d, P &r )
{
    P n; n.x = d.y - c.y; n.y = c.x - d.x;
    double denom = n.x * ( b.x - a.x ) + n.y * ( b.y - a.y );
    if( fabs( denom ) < EPS ) return false;
    double num = n.x * ( a.x - c.x ) + n.y * ( a.y - c.y );
    double t = -num / denom;
    r.x = a.x + t * ( b.x - a.x );
    r.y = a.y + t * ( b.y - a.y );
    return true;
}

/*****************************
 * Line segment intersection *
 *****************************
 * Returns true iff two line segments:
 * (x[0],y[0])-(x[1],y[1]) and (x[2],y[2])-(x[3],y[3])
 * intersect. Call lineIntersect( x, y ) to get the point of intersection.
 * WARNING: Does not work for collinear line segments!
 * #include <vector>
 **/
template< class T >
// Params: x and y are coordinate arrays of two segment endpoints each.
bool lineSegIntersect( vector< T > &x, vector< T > &y )
{
    double ucrossv1 = ( x[1] - x[0] ) * ( y[2] - y[0] ) - ( y[1] - y[0] ) * ( x[2] - x[0] );
    double ucrossv2 = ( x[1] - x[0] ) * ( y[3] - y[0] ) - ( y[1] - y[0] ) * ( x[3] - x[0] );
    if( ucrossv1 * ucrossv2 > 0 ) return false;
    double vcrossu1 = ( x[3] - x[2] ) * ( y[0] - y[2] ) - ( y[3] - y[2] ) * ( x[0] - x[2] );
    double vcrossu2 = ( x[3] - x[2] ) * ( y[1] - y[2] ) - ( y[3] - y[2] ) * ( x[1] - x[2] );
    return( vcrossu1 * vcrossu2 <= 0 );
}

/***************************
 * Circle through 3 points *
 ***************************
 * Computes the circle containing the 3 given points.
 * The 3 points are
 *      (x[0], y[0]), (x[1], y[1]) and (x[2], y[2]).
 * The centre of the circle is returned as (r[0], r[1]).
 * The radius is returned normally. If the circle is
 * undefined (the points are collinear), -1.0 is returned.
 * #include <math.h>
 * REQUIRES: lineIntersect
 * FIELD TESTING: Passed UVA 190
 **/
// Params: x,y hold three points; r receives circle center.
double circle3pts( double x[], double y[], double r[] )
{
    double lix[4], liy[4];
    lix[0] = 0.5 * ( x[0] + x[1] ); liy[0] = 0.5 * ( y[0] + y[1] );
    lix[1] = lix[0] + y[1] - y[0];  liy[1] = liy[0] + x[0] - x[1];
    lix[2] = 0.5 * ( x[1] + x[2] ); liy[2] = 0.5 * ( y[1] + y[2] );
    lix[3] = lix[2] + y[2] - y[1];  liy[3] = liy[2] + x[1] - x[2];
    if( !lineIntersect( lix, liy, r ) ) return -1.0;
    return sqrt(
        ( r[0] - x[0] ) * ( r[0] - x[0] ) +
        ( r[1] - y[0] ) * ( r[1] - y[0] ) );
}

/*********************************************
 * Circle of a given radius through 2 points *
 *********************************************
 * Computes the center of a circle containing the 2 given
 * points. The circle has the given radius. The returned
 * center is never to the right of the vector
 * (x1, y1)-->(x2, y2).
 * If this is possible, returns true and passes the center
 * through the ctr array. Otherwise, returns false.
 * #include <math.h>
 * FIELD TESTING:
 *      - Valladolid 10136: Chocolate Chip Cookies
 **/
// Params: (x1,y1),(x2,y2) are points, r is radius, ctr receives center.
bool circle2ptsRad( double x1, double y1, double x2, double y2, double r, double ctr[2] )
{
    double d2 = ( x1 - x2 ) * ( x1 - x2 ) + ( y1 - y2 ) * ( y1 - y2 );
    double det = r * r / d2 - 0.25;
    if( det < 0.0 ) return false;
    double h = sqrt( det );
    ctr[0] = ( x1 + x2 ) * 0.5 + ( y1 - y2 ) * h;
    ctr[1] = ( y1 + y2 ) * 0.5 + ( x2 - x1 ) * h;
    return true;
}

/***************
 * Cut Polygon *
 ***************
 * Intersects a given convex polygon with a half-plane. The
 * half-plane is defined as the one on the left side of the
 * directed line a-->b. The polygon 'poly' is modified.
 * The half-plane is considered open, so if only one vertex
 * of the polygon remains after the cut, it is eliminated.
 * REQUIRES:
 *      - Pt must have members x and y.
 *      - lineIntersect( Pt, Pt, Pt, Pt )
 *      - dist2( Pt, Pt )
 * FIELD TESTING:
 *      - Valladolid 137: Polygon
 *      - Valladolid 10117: Nice Milk
 **/
template< class Pt >
// Params: poly is convex polygon; a,b define cutting directed line.
void cutPoly( list< Pt > &poly, Pt a, Pt b )
{
    if( !poly.size() ) return;
    
    // see if the last point of the polygon is inside
    bool lastin = leftTurn( a, b, poly.back() );
    
    // find the boundary points
    __typeof( poly.begin() ) fi = poly.end(), la = fi, fip = fi, lan = fi;
    for( __typeof( fi ) i = --poly.end(), j = poly.begin(); 
        j != poly.end(); i = j++ )
    {
        int thisin = leftTurn( a, b, *j );
        
        if( lastin && !thisin ) { la = i; lan = j; }
        if( !lastin && thisin ) { fi = j; fip = i; }
        
        lastin = thisin;
    }

    // see if we have crossed the line at all
    if( fi == poly.end() )
    {
        if( !lastin ) poly.clear();
        return;
    }
    
    // if we cut off a corner, insert a new point
    if( lan == fip )
    {
        poly.insert( lan, *lan );
        --lan;
    }
    
    // compute intersection points
    Pt r;
    lineIntersect( *la, *lan, a, b, r );
    *lan = r;
    lineIntersect( *fip, *fi, a, b, r );
    *fip = r;
    
    // erase the part that disappears
    __typeof( fi ) i = lan; ++i;
    while( i != fip )
    {
        if( i == poly.end() ) { i = poly.begin(); if( i == fip ) break; }
        poly.erase( i++ );
    }
    
    // clean up duplicate points
    if( dist2( *lan, *fip ) < EPS ) poly.erase( fip );
}

/******************************
 * Triangle Area from Medians *
 ******************************
 * Given the lengths of the 3 medians of a triangle,
 * returns the triangle's area, or -1 if it impossible.
 * WARNING: Deal with the case of zero area carefully.
 * #include <math.h>
 * FIELD TESTING:
 *      - Valladolid 10347: Medians
 **/
// Params: ma, mb, mc are triangle median lengths.
double triAreaFromMedians( double ma, double mb, double mc )
{
    double x = 0.5 * ( ma + mb + mc );
    double a = x * ( x - ma ) * ( x - mb ) * ( x - mc );
    if( a < 0.0 ) return -1.0;
    else return sqrt( a ) * 4.0 / 3.0;
}

/****************
 * Great Circle *
 ****************
 * Given two pairs of (latitude, longitude), returns the
 * great circle distance between them.
 * FIELD TESTING
 *      - Valladolid 535: Globetrotter
 **/
// Params: laa,loa and lab,lob are two latitude/longitude pairs.
double greatCircle( double laa, double loa, double lab, double lob )
{
    double PI = acos( -1.0 ), R = 6378.0;
    double u[3] = { cos( laa ) * sin( loa ), cos( laa ) * cos( loa ), sin( laa ) };
    double v[3] = { cos( lab ) * sin( lob ), cos( lab ) * cos( lob ), sin( lab ) };
    double dot = u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
    bool flip = false;
    if( dot < 0.0 )
    {
        flip = true;
        for( int i = 0; i < 3; i++ ) v[i] = -v[i];
    }
    double cr[3] = { u[1]*v[2] - u[2]*v[1], u[2]*v[0] - u[0]*v[2], u[0]*v[1] - u[1]*v[0] };
    double theta = asin( sqrt( cr[0]*cr[0] + cr[1]*cr[1] + cr[2]*cr[2] ) );
    double len = theta * R;
    if( flip ) len = PI * R - len;
    return len;
}
/****************
 * Convex Hull *
 ****************
 * Computes the convex hull of a set of points using
 * Andrew's monotonic chain algorithm.
 *
 * Returns the hull in counter-clockwise order.
 * The first point is NOT repeated at the end.
 *
 * If all points are collinear, returns the two
 * extreme endpoints.
 *
 * COMPLEXITY:
 *      O(n log n)
 *
 * REQUIRES:
 *      - struct P with members x, y
 *      - cross product / left turn test
 *      - #include <algorithm>
 *      - #include <vector>
 **/

// Params: a and b are points compared lexicographically by x then y.
bool cmpP( const P &a, const P &b )
{
    return a.x < b.x || ( a.x == b.x && a.y < b.y );
}

// cross product (OA x OB)
// Params: o is origin point, a and b are points forming vectors OA and OB.
double cross( P o, P a, P b )
{
    return ( a.x - o.x ) * ( b.y - o.y ) -
           ( a.y - o.y ) * ( b.x - o.x );
}

// Params: pts is the input point set.
vector< P > convexHull( vector< P > pts )
{
    int n = pts.size();
    vector< P > H;

    if( n <= 1 ) return pts;

    sort( pts.begin(), pts.end(), cmpP );

    // lower hull
    for( int i = 0; i < n; i++ )
    {
        while( H.size() >= 2 &&
               cross( H[ H.size()-2 ], H.back(), pts[i] ) <= 0 )
            H.pop_back();
        H.push_back( pts[i] );
    }

    // upper hull
    int lowerSize = H.size();
    for( int i = n-2; i >= 0; i-- )
    {
        while( (int)H.size() > lowerSize &&
               cross( H[ H.size()-2 ], H.back(), pts[i] ) <= 0 )
            H.pop_back();
        H.push_back( pts[i] );
    }

    // remove duplicate last point
    H.pop_back();

    return H;
}

// Area of Triangle - Union
/************************
 * Area of Rectangles  *
 ************************
 * Computes the area of union of axis-aligned rectangles.
 *
 * Rectangle i:
 *      (x1[i], y1[i]) to (x2[i], y2[i])
 *
 * Algorithm:
 *      - Sweep line on x
 *      - Segment tree on y
 *
 * Complexity:
 *      O(n log n)
 *
 * FIELD TESTING:
 *      - CSES: Area of Rectangles
 **/


struct Event
{
    long long x;
    int y1, y2;
    int type;   // +1 = add, -1 = remove
    // Params: e is the event compared by x-coordinate.
    bool operator<( const Event &e ) const
    {
        return x < e.x;
    }
};

vector<long long> ys;
vector<Event> events;

struct SegTree
{
    int cnt;
    long long len;
};

SegTree st[800000];   // 4 * max compressed y

// Params: node is segment-tree index, [l,r) is covered y-range index interval.
void pull( int node, int l, int r )
{
    if( st[node].cnt > 0 )
        st[node].len = ys[r] - ys[l];
    else if( r - l == 1 )
        st[node].len = 0;
    else
        st[node].len = st[node*2].len + st[node*2+1].len;
}

// Params: update [ql,qr) by val on node covering [l,r).
void update( int node, int l, int r, int ql, int qr, int val )
{
    if( qr <= l || r <= ql ) return;
    if( ql <= l && r <= qr )
    {
        st[node].cnt += val;
        pull( node, l, r );
        return;
    }
    int mid = ( l + r ) >> 1;
    update( node*2, l, mid, ql, qr, val );
    update( node*2+1, mid, r, ql, qr, val );
    pull( node, l, r );
}

#if 0
// Params: none.
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> x1(n), y1(n), x2(n), y2(n);

    for( int i = 0; i < n; i++ )
    {
        cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
        ys.push_back( y1[i] );
        ys.push_back( y2[i] );
    }

    // coordinate compression
    sort( ys.begin(), ys.end() );
    ys.erase( unique( ys.begin(), ys.end() ), ys.end() );

    for( int i = 0; i < n; i++ )
    {
        int cy1 = lower_bound( ys.begin(), ys.end(), y1[i] ) - ys.begin();
        int cy2 = lower_bound( ys.begin(), ys.end(), y2[i] ) - ys.begin();
        events.push_back( { x1[i], cy1, cy2, +1 } );
        events.push_back( { x2[i], cy1, cy2, -1 } );
    }

    sort( events.begin(), events.end() );

    long long area = 0;
    long long prevX = events[0].x;

    for( int i = 0; i < (int)events.size(); i++ )
    {
        long long curX = events[i].x;
        long long dx = curX - prevX;
        area += dx * st[1].len;

        // process all events at curX
        while( i < (int)events.size() && events[i].x == curX )
        {
            update( 1, 0, ys.size()-1,
                    events[i].y1, events[i].y2,
                    events[i].type );
            i++;
        }
        i--;
        prevX = curX;
    }

    cout << area << "\n";
    return 0;
}
#endif

/***********************************
 * Maximum Manhattan Distance      *
 ***********************************
 * For two points:
 *      P(x1, y1), Q(x2, y2)
 *
 * Manhattan distance is defined as:
 *
 *      |x1 - x2| + |y1 - y2|
 *
 * KEY OBSERVATION:
 *
 * |x1 - x2| + |y1 - y2| =
 * max of:
 *      (x + y)_1 - (x + y)_2
 *      (x - y)_1 - (x - y)_2
 *
 * Therefore, for a set of points,
 * the maximum Manhattan distance is:
 *
 * max(
 *      max(x + y) - min(x + y),
 *      max(x - y) - min(x - y)
 * )
 *
 * GEOMETRIC / INTERSECTION VIEW:
 *
 * Consider the lines:
 *      x + y = constant   (45° diagonal)
 *      x - y = constant   (-45° diagonal)
 *
 * The farthest pair of points must lie
 * on the intersection of the extreme
 * such diagonal lines.
 *
 * ONLINE VERSION:
 *
 * As each point is read:
 *      - Update min/max of (x + y)
 *      - Update min/max of (x - y)
 *      - Current maximum Manhattan
 *        distance can be reported
 *
 * Complexity:
 *      O(1) per point
 *
 * FIELD TESTING:
 *      - CSES: Maximum Manhattan Distance
 **/

// Params: none.
void solve() {
    int n;
    cin >> n;

    long long mnX , mxX;
    long long mnY, mxY;

    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        
        // Transform coordinates
        long long xx = x + y;
        long long yy = x - y;

        // Initialize on first point
        if (i == 0) {
            mnX = mxX = xx;
            mnY = mxY = yy;
        }

        // Maintain extreme projections
        mnX = min(mnX, xx);
        mxX = max(mxX, xx);
        mnY = min(mnY, yy);
        mxY = max(mxY, yy);

        // Current maximum Manhattan distance
        cout << max(mxX - mnX, mxY - mnY) << endl;
    }
}

#if 0
// Params: none.
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    solve();
    return 0;
}
#endif


/***********************************
 * Lattice Polygon Utilities       *
 ***********************************
 * A lattice point is a point with
 * integer coordinates.
 *
 * This code computes:
 *   - I : number of interior lattice points
 *   - B : number of boundary lattice points
 *
 * for a simple polygon with integer
 * coordinates.
 *
 * Based on Pick's Theorem:
 *
 *      Area = I + B/2 - 1
 *
 * Rearranged:
 *
 *      I = (2*Area - B + 2) / 2
 *
 * Where:
 *      Area = polygon area
 *      B    = lattice points on boundary
 **/

struct point{
    ll x;
    ll y;
};

/***********************************
 * Lattice Points on a Line Segment *
 ***********************************
 * Given a vector (dx, dy), the number
 * of lattice points on the line segment
 * between the endpoints (inclusive) is:
 *
 *      gcd(|dx|, |dy|) + 1
 *
 * This comes from number theory:
 * integer points occur at uniform steps
 * along the direction vector.
 **/
// Params: x and y are delta coordinates of a segment vector.
ll getLineLattice(ll x,ll y){
    if( x<0 ) x = -x;
    if( y<0 ) y = -y;
    return __gcd(x,y) + 1;
}

/***********************************
 * Polygon Area (Shoelace Formula) *
 ***********************************
 * Computes twice the area of a polygon
 * with integer coordinates.
 *
 * Formula used:
 *      Area = 1/2 * |Σ (x_i - x_{i+1})
 *                        * (y_i + y_{i+1})|
 *
 * The returned value is:
 *      2 * Area
 *
 * (absolute value taken)
 **/
// Params: fig is the polygon vertex list in order.
ll getArea(const vector<point>& fig) {
    ll res = 0;
    for (unsigned i = 0; i < fig.size(); i++) {
        point p = i ? fig[i - 1] : fig.back();
        point q = fig[i];
        res += (p.x - q.x) * (p.y + q.y);
    }
    return labs(res);
}

#if 0
// Params: none.
int main(){
    cout<<fixed<<setprecision(20);

    int n;
    cin>>n;

    /***********************************
     * Read polygon vertices           *
     ***********************************
     * Polygon is assumed to be:
     *   - simple
     *   - vertices given in order
     *   - integer coordinates
     **/
    vector<point> pol;
    for(int i=0;i<n;i++){
        int a,b;
        cin>>a>>b;
        pol.push_back({a,b});
    }

    /***********************************
     * Compute doubled area            *
     ***********************************/
    ll area = getArea(pol);

    /***********************************
     * Count boundary lattice points   *
     ***********************************
     * For each polygon edge:
     *   gcd(|dx|, |dy|) + 1 gives
     *   lattice points including both
     *   endpoints.
     *
     * Since each vertex is counted
     * twice, subtract n at the end.
     **/
    ll B = 0;
    for(int i=0;i<pol.size();i++){
        B += getLineLattice(
                pol[i].x - pol[(i+1)%n].x,
                pol[i].y - pol[(i+1)%n].y
             );
    }
    B -= n;

    /***********************************
     * Apply Pick's Theorem            *
     ***********************************
     * Area = I + B/2 - 1
     *
     * Using doubled area:
     *   2*Area = 2*I + B - 2
     *
     * => I = (2*Area - B + 2) / 2
     **/
    ll I = (area + 2 - B) / 2;

    /***********************************
     * Output:
     *   I = interior lattice points
     *   B = boundary lattice points
     ***********************************/
    cout<<I<<" "<<B;
}
#endif


/***********************************
 * Point Structure                 *
 ***********************************
 * Simple 2D point with integer
 * coordinates and basic vector
 * operations.
 **/
struct pt{
    ll x;
    ll y;
    // Params: p is the added point vector.
    pt operator+(pt p) {return {x+p.x, y+p.y};}
    // Params: p is the subtracted point vector.
    pt operator-(pt p) {return {x-p.x, y-p.y};}
    // Params: d is a scalar multiplier.
    pt operator*(ll d) {return {x*d, y*d};}
    // Params: d is a scalar divisor.
    pt operator/(ll d) {return {x/d, y/d};}
};

/***********************************
 * Point on Polygon Boundary Test  *
 ***********************************
 * Checks whether a point pn lies
 * exactly on any edge of the polygon.
 *
 * For each edge:
 *  - Check collinearity using cross product
 *  - Check if pn lies within the
 *    bounding box of the edge
 *
 * Returns true if pn is on boundary.
 *
 * Works for integer coordinates.
 **/
template<class T>
// Params: polygon is closed polygon vertices and pn is query point.
bool onBoundary(vector<pair<T,T> >&polygon,pair<T,T> pn)
{
    int n=(int)polygon.size();
    for(int i=0;i<n-1;i++)
    {
        T tmp=(polygon[i].first-pn.first)*(polygon[i+1].second-pn.second)
                -(polygon[i+1].first-pn.first)*(polygon[i].second-pn.second);
        if(tmp==0
           &&((pn.first>=polygon[i].first&&pn.first<=polygon[i+1].first)||(pn.first<=polygon[i].first&&pn.first>=polygon[i+1].first))
           &&((pn.second>=polygon[i].second&&pn.second<=polygon[i+1].second)||(pn.second<=polygon[i].second&&pn.second>=polygon[i+1].second)))
        {
            return true;
        }
    }
    return false;
}

/***********************************
 * Cross Product (Orientation)     *
 ***********************************
 * Returns the signed area of the
 * parallelogram formed by:
 *
 *      (p1 - p0) x (p2 - p0)
 *
 * > 0 : left turn
 * < 0 : right turn
 * = 0 : collinear
 **/
template <class T>
inline
// Params: p0 is origin, p1 and p2 define two vectors for oriented area.
T cross(pair<T,T> p0,pair<T,T> p1,pair<T,T> p2)
{
    return (p1.first-p0.first)*(p2.second-p0.second)
         - (p1.second-p0.second)*(p2.first-p0.first);
}

/***********************************
 * Winding Number Point-in-Polygon *
 ***********************************
 * Determines whether a point lies
 * inside a polygon using the
 * winding number algorithm.
 *
 * IDEA:
 *  - Traverse polygon edges
 *  - Count upward and downward
 *    crossings of a horizontal ray
 *  - Increment/decrement winding
 *    number based on orientation
 *
 * RESULT:
 *  - wn != 0  → point is INSIDE
 *  - wn == 0  → point is OUTSIDE
 *
 * ASSUMPTIONS:
 *  - polygon is simple
 *  - polygon[n] == polygon[0]
 *
 * Robust for concave polygons.
 *
 * FIELD TESTING:
 *  - LightOJ
 *  - Timus
 *  - CSES
 **/
template<class T>
// Params: polygon is closed polygon vertices and pn is query point.
int wnPnPolygon(vector<pair<T,T> >& polygon,pair<T,T> pn)
{
    int n=(int)polygon.size();
    int wn=0;

    for(int i=0;i<n-1;i++)
    {
        // upward crossing
        if(polygon[i].second<=pn.second)
        {
            if(polygon[i+1].second>pn.second
               &&cross(pn,polygon[i],polygon[i+1])>0)
            {
                ++wn;
            }
        }
        // downward crossing
        else if(polygon[i+1].second<=pn.second
                &&cross(pn,polygon[i],polygon[i+1])<0)
        {
            --wn;
        }
    }
    return wn;
}

#if 0
// Params: none.
int main(){
    //FASTIO;

    int n,m;
    cin>>n>>m;

    /***********************************
     * Read polygon vertices           *
     ***********************************
     * Polygon is closed by pushing
     * the first vertex again at the end.
     **/
    vector<pair<ll,ll>> poly;
    for(int i=0;i<n;i++){
        int a,b;
        cin>>a>>b;
        poly.push_back({a,b});
    }
    poly.push_back(poly[0]);

    /***********************************
     * Query points                   *
     ***********************************
     * For each query point:
     *  1) Check boundary
     *  2) Else use winding number
     *
     * Output:
     *  - "BOUNDARY"
     *  - "INSIDE"
     *  - "OUTSIDE"
     **/
    while(m--){
        int a,b;
        cin>>a>>b;

        bool onEdge = onBoundary(poly,{a,b});
        if( onEdge )
            cout<<"BOUNDARY\n";
        else {
            int windingNumber = wnPnPolygon(poly,{a,b});
            if( windingNumber )
                cout<<"INSIDE\n";
            else
                cout<<"OUTSIDE\n";
        }
    }
}
#endif