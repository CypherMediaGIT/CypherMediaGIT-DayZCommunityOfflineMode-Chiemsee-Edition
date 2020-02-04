static string FormatFloat( float value, int decimals ) 
{
    if ( !value.ToString().Contains(".") ) return value.ToString();
	
    string result = "";
    array<string> output = new array<string>;

    value.ToString().Split(".", output);

    if ( output.Count() == 0 ) return value.ToString();

    if ( decimals == 0 ) return output.Get(0);

    string right = output.Get(1).Substring(0, decimals);
    result = output.Get(0) + "." + right;
    return result;
}

static string VectorToString( vector vec )
{
    string result = vec.ToString();
    result.Replace( "<", "" );
    result.Replace( ">", "" );
    result.Replace( ",", "" );

    return result;
}

static string VectorToString( vector vec, int decimals ) 
{
    string result = "";
    result = FormatFloat(vec[0], decimals) + "|" + FormatFloat(vec[1], decimals) + "|" + FormatFloat(vec[2], decimals);

    return result;
}

static TStringArray GetChildrenFromBaseClass( string strConfigName, string strBaseClass )
{
    string child_name = "";
    int count = GetGame().ConfigGetChildrenCount ( strConfigName );
    TStringArray class_names = new TStringArray;

    for (int p = 0; p < count; p++)
    {
        GetGame().ConfigGetChildName ( strConfigName, p, child_name );

        if ( GetGame().IsKindOf(child_name, strBaseClass ) && ( child_name != strBaseClass ) )
        {
            class_names.Insert(child_name);
        }
    }

    return class_names;
}

static TVectorArray GetSpawnPoints()
{
    return { "2574.85 0 5909.21", "165.66 0 747.01", "1449.02 0 105.64", "5075.93 0 216.29",
			 "9950.57 0  668.25", "1153.24 0 1477.77", "2819.27 0 1252.10", "3028.05 0 1643.43",
			 "4637.10 0 1725.94", "1143.33 0 2567.97", "2302.92 0 2612.98", "3926.34 0 2674.24",
			 "3049.31 0 2971.17", "2317.30 0 3312.48", "1857.22 0 3561.90", "3097.44 0 4297.53",
			 "6364.29 0 4714.61", "8228.38 0 4379.55", "8856.00 0 4887.14", "2021.00 0 5214.70",
			 "4668.35 0 5360.98", "6390.55 0 5931.09", "7166.31 0 5404.11", "8305.27 0 6452.43",
			 "7000.66 0 6564.95", "9346.09 0 8809.11", "4658.98 0 7576.39", "5107.19 0 8413.42",
			 "6436.80 0 9176.06", "7396.98 0 9521.12", "6154.88 0 9706.15", "3318.11 0 8738.48",
			 "2292.92 0 8588.45", "1188.34 0 9552.37", "2512.96 0 9878.68" };
}

static set< Object > GetObjectsAt( vector from, vector to, Object ignore = NULL, float radius = 0.5, Object with = NULL )
{
    vector contact_pos;
    vector contact_dir;
    int contact_component;

    set< Object > geom = new set< Object >;
    set< Object > view = new set< Object >;

    DayZPhysics.RaycastRV( from, to, contact_pos, contact_dir, contact_component, geom, with, ignore, false, false, ObjIntersectGeom, radius );
    DayZPhysics.RaycastRV( from, to, contact_pos, contact_dir, contact_component, view, with, ignore, false, false, ObjIntersectView, radius );

    if ( geom.Count() > 0 ) 
    {
        return geom;
    }
    if ( view.Count() > 0 ) 
    {
        return view;
    }
    return NULL;
}

static Object GetPointerObject( Object ignore = NULL, float radius = 0.5, Object with = NULL )
{
    vector dir = GetGame().GetPointerDirection();

    vector from = GetGame().GetCurrentCameraPosition();

    vector to = from + ( dir * 10000 );

    auto objs = GetObjectsAt( from, to, ignore, radius, with );

    if( objs.Count() > 0 )
    {
        return objs[ 0 ];
    }

    return NULL;
}

static Object GetCursorObject()
{
    vector rayStart = GetGame().GetCurrentCameraPosition();
    vector rayEnd = rayStart + GetGame().GetCurrentCameraDirection() * 10000;

    auto objs = GetObjectsAt( rayStart, rayEnd );

    if( objs.Count() > 0 )
    {
        return objs[ 0 ];
    }

    return NULL;
}

static vector GetPointerPos()
{
    if ( !GetPlayer() )
    {
        return "0 0 0";
    }

    vector dir = GetGame().GetPointerDirection();

    vector from = GetGame().GetCurrentCameraPosition();

    vector to = from + ( dir * 10000 );

    vector rayStart = from;
    vector rayEnd = to;
    vector hitPos;
    vector hitNormal;
    int hitComponentIndex;
    DayZPhysics.RaycastRV(rayStart, rayEnd, hitPos, hitNormal, hitComponentIndex, NULL, NULL, GetPlayer());

    return hitPos;
}

static vector GetCursorPos()
{
    if ( !GetPlayer() )
    {
        return "0 0 0";
    }

    vector rayStart = GetGame().GetCurrentCameraPosition();
    vector rayEnd = rayStart + GetGame().GetCurrentCameraDirection() * 10000;
    vector hitPos;
    vector hitNormal;
    int hitComponentIndex;
    DayZPhysics.RaycastRV(rayStart, rayEnd, hitPos, hitNormal, hitComponentIndex, NULL, NULL, GetPlayer());

    return hitPos;
}

static void Message( string txt ) 
{
    GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(CCDirect, "", txt, ""));
}

static Weapon GetWeaponInHands()
{
    Weapon weapon_in_hands;
    if( GetPlayer() && GetPlayer().GetItemInHands() ) Class.CastTo(weapon_in_hands,  GetPlayer().GetItemInHands());

    return weapon_in_hands;
}

static MissionBase GetMission()
{
    return MissionBase.Cast( GetGame().GetMission() );
}

static CommunityOfflineClient GetClientMission()
{
    return CommunityOfflineClient.Cast( GetGame().GetMission() );
}

static CommunityOfflineServer GetServerMission()
{
    return CommunityOfflineServer.Cast( GetGame().GetMission() );
}

static ref PlayerBase GetPlayer()
{
    return GetGame().GetPlayer();
}

static bool SHIFT()
{
    return( ( KeyState( KeyCode.KC_LSHIFT ) > 0 ) || ( KeyState( KeyCode.KC_RSHIFT ) > 0 ) );
}

static bool CTRL()
{
    return( ( KeyState( KeyCode.KC_LCONTROL ) > 0 ) || ( KeyState( KeyCode.KC_RCONTROL ) > 0 ) );
}

static bool ALT()
{
    return( ( KeyState( KeyCode.KC_LMENU ) > 0 ) || ( KeyState( KeyCode.KC_RMENU ) > 0 ) );
}

static bool WINKEY()
{
    return( ( KeyState( KeyCode.KC_LWIN ) > 0 ) || ( KeyState( KeyCode.KC_RWIN ) > 0 ) );
}

/*
static Weapon_Base CreateWeapon( PlayerBase oPlayer )
{
    Weapon_Base oWpn = Weapon_Base.Cast(oPlayer.GetInventory().CreateInInventory( "M4A1_Black" ));
    oWpn.GetInventory().CreateAttachment( "M4_Suppressor" );
    oWpn.GetInventory().CreateAttachment( "M4_RISHndgrd_Black" );
    oWpn.GetInventory().CreateAttachment( "M4_MPBttstck_Black" );
    oWpn.GetInventory().CreateAttachment( "ACOGOptic" );

    return oWpn;
}
*/

static Weapon_Base CreateWeapon( PlayerBase oPlayer, string sWeapon )
{
    Weapon_Base oWpn = Weapon_Base.Cast(oPlayer.GetInventory().CreateInInventory( sWeapon ));
    oWpn.GetInventory().CreateAttachment( "PistolSuppressor" );
    EntityAI optic = oWpn.GetInventory().CreateAttachment( "ReflexOptic" );
    optic.GetInventory().CreateAttachment("Battery9V");

    return oWpn;
}

static PlayerBase CreateCustomDefaultCharacter()
{
    PlayerBase oPlayer = PlayerBase.Cast( GetGame().CreatePlayer( NULL, GetGame().CreateRandomPlayer(), GetSpawnPoints().GetRandomElement(), 0, "NONE") );

    EntityAI item = NULL;

    item = oPlayer.GetInventory().CreateInInventory( "AviatorGlasses" );
    item = oPlayer.GetInventory().CreateInInventory( "MilitaryBeret_UN" );
    item = oPlayer.GetInventory().CreateInInventory( "M65Jacket_Black" );
    item = oPlayer.GetInventory().CreateInInventory( "TacticalGloves_Black" );
    item = oPlayer.GetInventory().CreateInInventory( "HunterPants_Autumn" );
    item = oPlayer.GetInventory().CreateInInventory( "MilitaryBoots_Black" );
    item = oPlayer.GetInventory().CreateInInventory( "AliceBag_Camo" );
    item = oPlayer.GetInventory().CreateInInventory( "Shovel" );

    Weapon_Base oWpn = CreateWeapon( oPlayer, "UMP45" );
    Magazine oMag = Magazine.Cast( oPlayer.GetInventory().CreateInInventory( "Mag_UMP_25Rnd" ) );
    oPlayer.GetDayZPlayerInventory().PostWeaponEvent( new WeaponEventAttachMagazine( oPlayer, oMag ) );
    item = oPlayer.GetInventory().CreateInInventory( "Mag_UMP_25Rnd" );

    oPlayer.LocalTakeEntityToHands( oWpn );
    oPlayer.SetQuickBarEntityShortcut( oWpn, 0, true );
    oPlayer.SetQuickBarEntityShortcut( oMag, 1, true );

    return oPlayer;
}

static string FileAttributeToString( FileAttr attr )
{
    string fileType = "";
    if ( attr & FileAttr.DIRECTORY )
    {
        fileType = fileType + "DIRECTORY";
    }
    if ( attr & FileAttr.HIDDEN )
    {
        fileType = fileType + "HIDDEN";
    }
    if ( attr & FileAttr.READONLY )
    {
        fileType = fileType + "READONLY";
    }
    if ( attr & FileAttr.INVALID )
    {
        fileType = fileType + "INVALID";
    }
    return fileType;
}

static vector SnapToGround(vector pos)
{
    float pos_x = pos[0];
    float pos_z = pos[2];
    float pos_y = GetGame().SurfaceY( pos_x, pos_z );
    vector tmp_pos = Vector( pos_x, pos_y, pos_z );
    tmp_pos[1] = tmp_pos[1] + pos[1];

    return tmp_pos;
}

static bool m_GodMode; // move these to player saves? Edit: Jacob says "yes"
static bool m_OldAiming;
static bool bc_Visible;

static void SnapToGroundNew( Object object ) 
{
    vector pos = object.GetPosition();
    pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
    
    vector clippingInfo[2];
    vector objectBBOX[2];
    
    object.GetCollisionBox( objectBBOX );
    object.ClippingInfo( clippingInfo );

    //float clipY = objectBBOX[1][1] / 2.0//- clippingInfo[0][1];
    //pos[1] = pos[1] + objectBBOX[1][1] - clipY;
    pos[1] = pos[1] + clippingInfo[1][1] / 2.0;//objectBBOX[0][1] - clipY

    object.SetPosition(pos);

    ForceTargetCollisionUpdate( object );
}

static void ForceTargetCollisionUpdate( Object oObj )
{
    if ( !oObj ) return;

    vector roll = oObj.GetOrientation();
    roll [ 2 ] = roll [ 2 ] - 1;
    oObj.SetOrientation( roll );
    roll [ 2 ] = roll [ 2 ] + 1;
    oObj.SetOrientation( roll );
}

static void ToggleCursor()
{
    if ( GetGame().GetInput().HasGameFocus( INPUT_DEVICE_MOUSE ) )
    {
        GetGame().GetInput().ChangeGameFocus( 1 );
        GetGame().GetUIManager().ShowUICursor( true );
    }
    else
    {
        GetGame().GetUIManager().ShowUICursor( false );
        GetGame().GetInput().ResetGameFocus();
    }
}

/*
    Token types:
     0 - error, no token
     1 - defined token (special characters etc. . / * )
     2 - quoted string. Quotes are removed -> TODO
     3 - alphabetic string
     4 - number
     5 - end of line -> TODO
*/
static bool CheckStringType( string str, int type ) 
{
    for(int i = 0; i<str.Length(); i++ ) 
    {
        string character = str.Get(i);
        string token;
        int result = character.ParseStringEx(token);
        if ( result == type ) return true;
    }
    return false;
}

string GetRandomChildFromBaseClass( string strConfigName, string strBaseClass, int minScope = -1 )
{
    string child_name = "";
    int count = GetGame().ConfigGetChildrenCount ( strConfigName );
    array< string > class_names = new array<string>;

    for ( int p = 0; p < count; p++ )
    {
        GetGame().ConfigGetChildName ( strConfigName, p, child_name );

        if( ( minScope != -1 ) && ( GetGame().ConfigGetInt( strConfigName + " " + child_name + " scope" ) < minScope ) ) continue;

        if ( GetGame().IsKindOf( child_name, strBaseClass ) && ( child_name != strBaseClass ) )
        {
            class_names.Insert( child_name );
        }
    }

    return class_names.GetRandomElement();
}
