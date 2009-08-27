/*      @ file:            @ last modified:                    @ author:
 *      CPlant.h             31-07-2009 21:19                    Zborowski S.
 *
 *      @ Description:
 *      Header for L-system plants class.
 */

#ifndef _CPLANT_H
#define _CPLANT_H
#include <string>
#include <sstream>
#include <vector>
#include "common.h"
#include "Vector3d.h"

#include "CLeaf.h"
#include "CRoot.h"
#include "CBranch.h"

// good leafx: [LL]P[L][L][L]
// with formula: P[LL][L]P[L] and rootx: PP

//another big tree
// good leafx: [LL]P[L][L][L]
// with formula: P[P[L][L]][LL][P[[L][L][L][L]]][L]P[L][P[L][L]] and rootx: P

#define PLANT_SHOW_TRIS         0x08
#define PLANT_RANDOM_ANGLES     0x0a
#define PLANT_USE_GRAVITY       0xa0


typedef struct
{
    float cr, cg, cb;
    float x0, y0, z0;
    float x1, y1, z1;
    bool is_root;
} line3;

typedef struct
{
    float x0, y0, z0;
    float x1, y1, z1;
    float x2, y2, z2;
    float x3, y3, z3;
    bool is_root;
} square3;

/*typedef struct
{
    Matrix44 M;
    bool is_root;
} pien_t;
*/
typedef struct
{
    float x0, y0, z0;
    float x1, y1, z1;
    float x2, y2, z2;
    float x3, y3, z3;
    float x4, y4, z4;
    float x5, y5, z5;
    float x6, y6, z6;
    float x7, y7, z7;
    bool is_root;
} square_strip;


class CPlant
{
    public:
    CPlant();
    CPlant( std::string formula );
    CPlant( std::string formula, std::string root_r, std::string leaf_r, std::string lbracket_r, std::string rbracket_r );
    bool CheckFormula();
    inline std::string GetExtendedFormula()
    {
        return m_formula.str();
    }
    void ExpandFormula( uint N );
    //void GeneratePlant( float x0, float y0, float z0, double angle, double Zangle, double len );
    //void GeneratePlant3d( float x0, float y0, float z0, float width, double angle, double Zangle, double len );

    ///
    void GeneratePlant3dStrips( float x0, float y0, float z0, float len, float width, double angle, double Zangle );
    ////
    /////
    void GeneratePlant( Vector3d v, number len, number width, number angle, number zangle );
    void GeneratePlantB( Vector3d v, number len, number width, number angle, number zangle );
    /////
    void GeneratePlant3d8Strips( number x0, number y0, number z0, number len, number width, number angle, number Zangle );
    ////
    void DrawPlantFromBuffer3dStrips( void );
    ///

    uint GetRootsNumber( void );
    uint GetLeafsNumber( void );

    //void DrawPlant( float x0, float y0, double angle, double len );
    //void DrawPlantFromBuffer( void );
    void DrawPlantFromBuffer3d( void );

    void SetOptions( u8 o );
    /// /// /// ///
    void GenerateDisplayList( void );
    void Simplify( void );


    ~CPlant();


    void set( std::string formula, std::string root_r, std::string leaf_r, std::string lbracket_r, std::string rbracket_r );


    std::stringstream m_formula;
    GLuint displayList;
    private:



    uint m_currpos, m_currpos2, m_currpos3d, m_currpos3dm;

    std::vector< line3 > m_Lines;
    std::vector< line3 >::iterator m_Iterator;

    std::vector< square3 > m_Squares;
    std::vector< square3 >::iterator m_Iterator_s;

    std::vector< square_strip > m_Strips;
    std::vector< square_strip >::iterator m_Iterator_m;






    /// NEW ////////////////////////////////////////////////////////////////////////////////
    std::stringstream                   m_formula_tmpfornow;
    uint                                m_formula_pos;

    std::string                         m_root_r;
    std::string                         m_leaf_r;
    std::string                         m_lbracket_r;
    std::string                         m_rbracket_r;
    std::string                         m_plus_r;
    std::string                         m_minus_r;

    std::vector< CRoot >                m_Roots;
    std::vector< CRoot >::iterator      m_Roots_Iter;
    std::vector< CLeaf >                m_Leafs;
    std::vector< CLeaf >::iterator      m_Leafs_Iter;

    std::vector< CBranch >              m_Branches;
    std::vector< CBranch >::iterator    m_Branches_Iter;


    bool                                m_Tris;
    bool                                m_Random;
    bool                                m_Gravity;

};

#endif // _CPLANT_H
