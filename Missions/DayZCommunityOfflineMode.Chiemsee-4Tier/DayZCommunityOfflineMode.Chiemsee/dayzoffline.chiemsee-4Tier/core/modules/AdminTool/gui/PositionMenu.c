class PositionMenu extends PopupMenu
{
	protected TextListboxWidget m_LstPositionList;
	protected EditBoxWidget m_TxtSelectedX;
	protected EditBoxWidget m_TxtSelectedY;
	protected EditBoxWidget m_TxtCurrentX;
	protected EditBoxWidget m_TxtCurrentY;
	protected ButtonWidget m_TeleportButton;
	protected ButtonWidget m_CancelButton;

	autoptr map< string, vector > Positions = new map< string, vector >;

    protected bool m_bOverCurrentPos;

	void PositionMenu()
	{
	    m_bOverCurrentPos = false;

        Positions.Insert( "Hochstatt", "2574.85 0 5909.21" );
        Positions.Insert( "Bachham", "165.66 0 747.01" );
        Positions.Insert( "Urschalling", "1449.02 0 105.64" );
        Positions.Insert( "Chiemseepark Felden", "5075.93 0 216.29" );
        Positions.Insert( "Ubursee", "9950.57 0  668.25" );
		Positions.Insert( "Hub", "1153.24 0 1477.77" );
		Positions.Insert( "Mitterweg", "2819.27 0 1252.10" );
		Positions.Insert( "Sieggenham", "3028.05 0 1643.43" );
		Positions.Insert( "Prien", "4637.10 0 1725.94" );
		Positions.Insert( "Pinswang", "1143.33 0 2567.97" );
		Positions.Insert( "Otterkring", "2302.92 0 2612.98" );
		Positions.Insert( "Osternach", "3926.34 0 2674.24" );
		Positions.Insert( "Westernach", "3049.31 0 2971.17" );
		Positions.Insert( "Burgensdorf", "2317.30 0 3312.48" );
		Positions.Insert( "Rimsting", "1857.22 0 3561.90" );
		Positions.Insert( "Mauerkirchen", "3097.44 0 4297.53" );
		Positions.Insert( "Grune Insel", "6364.29 0 4714.61" );
		Positions.Insert( "Nichts", "8228.38 0 4379.55" );
		Positions.Insert( "Sud-Ost Flugplatz", "8856.00 0 4887.14" );
		Positions.Insert( "Antwort", "2021.00 0 5214.70" );
		Positions.Insert( "Camp Refugi", "4668.35 0 5360.98" );
		Positions.Insert( "Oberleiten", "6390.55 0 5931.09" );
		Positions.Insert( "Mittermuhle", "7166.31 0 5404.11" );
		Positions.Insert( "Gstadt", "8305.27 0 6452.43" );
		Positions.Insert( "Brietbrunn", "7000.66 0 6564.95" );
		Positions.Insert( "Gollenhausen", "9346.09 0 8809.11" );
		Positions.Insert( "Stein", "4658.98 0 7576.39" );
		Positions.Insert( "Eggstatt", "5107.19 0 8413.42" );
		Positions.Insert( "Obing", "6436.80 0 9176.06" );
		Positions.Insert( "Oberndorf", "7396.98 0 9521.12" );
		Positions.Insert( "Weitmoos", "6154.88 0 9706.15" );
		Positions.Insert( "Hamhof", "3318.11 0 8738.48" );
		Positions.Insert( "Bad Endorf", "2292.92 0 8588.45" );
		Positions.Insert( "Jolling", "1188.34 0 9552.37" );
		Positions.Insert( "Teisenham", "2512.96 0 9878.68" );
        //Positions.Insert( "", "" );
	}

	void ~PositionMenu()
	{
	}

	void Init()
	{
		m_LstPositionList = TextListboxWidget.Cast( layoutRoot.FindAnyWidget("tls_ppp_pm_positions_list") );
		m_TxtSelectedX = EditBoxWidget.Cast( layoutRoot.FindAnyWidget("pnl_ppp_pm_selected_x_value") );
		m_TxtSelectedY = EditBoxWidget.Cast( layoutRoot.FindAnyWidget("pnl_ppp_pm_selected_y_value") );
		m_TxtCurrentX = EditBoxWidget.Cast( layoutRoot.FindAnyWidget("pnl_ppp_pm_current_x_value") );
		m_TxtCurrentY = EditBoxWidget.Cast( layoutRoot.FindAnyWidget("pnl_ppp_pm_current_y_value") );
		m_TeleportButton = ButtonWidget.Cast( layoutRoot.FindAnyWidget("btn_ppp_pm_teleport") );
		m_CancelButton = ButtonWidget.Cast( layoutRoot.FindAnyWidget("btn_ppp_pm_cancel") );

        for ( int nPosition = 0; nPosition < Positions.Count(); nPosition++ )
        {
            m_LstPositionList.AddItem( Positions.GetKey( nPosition ), NULL, 0 );
        }
	}

	override void OnShow()
	{
        vector player_pos = COM_GetPB().GetPosition();

        m_TxtCurrentX.SetText( player_pos[0].ToString() );
		m_TxtCurrentY.SetText( player_pos[2].ToString() );
	}

	override void OnHide()
	{

	}

	override bool OnMouseEnter(Widget w, int x, int y)
	{
        if ( w == m_TxtCurrentX || w == m_TxtCurrentY )
        {
            m_bOverCurrentPos = true;
        }

		return false;
	}

	override bool OnMouseLeave( Widget w, Widget enterW, int x, int y )
	{
        if ( w == m_TxtCurrentX || w == m_TxtCurrentY )
        {
            m_bOverCurrentPos = false;
        }

		return false;
	}

	override bool OnKeyPress( Widget w, int x, int y, int key )
	{
		if ( m_bOverCurrentPos )
		{
            m_TxtSelectedX.SetText( "" );
            m_TxtSelectedY.SetText( "" );
		}

		return false;
	}

	override bool OnClick( Widget w, int x, int y, int button )
	{
		if ( w == m_TeleportButton )
		{
		    float pos_x = 0;
            float pos_y = 0;

		    if( ( m_TxtSelectedX.GetText() != "" ) && ( m_TxtSelectedY.GetText() != "" ) )
		    {
	            pos_x = m_TxtSelectedX.GetText().ToFloat();
                pos_y = m_TxtSelectedY.GetText().ToFloat();
		    }
		    else if( ( m_TxtCurrentX.GetText() != "" ) && ( m_TxtCurrentY.GetText() != "" ) )
		    {
                pos_x = m_TxtCurrentX.GetText().ToFloat();
                pos_y = m_TxtCurrentY.GetText().ToFloat();
		    }
		    else
		    {
		        PlayerBase oPlayer = COM_GetPB();
		        oPlayer.MessageStatus( "Invalid teleportation position!" );

		        return true;
		    }

			vector vPlayerPos;
			vPlayerPos[0] = pos_x;
			vPlayerPos[2] = pos_y;

			vPlayerPos = COM_SnapToGround( vPlayerPos );

			COM_GetPB().SetPosition( vPlayerPos );

			return true;
		}

		return false;
	}

	override bool OnItemSelected( Widget w, int x, int y, int row, int column, int oldRow, int oldColumn )
	{
		vector position = "0 0 0";

		if( !Positions.Find( GetCurrentPositionName(), position ) )
		{
			position = "0 0 0";
		}

		m_TxtSelectedX.SetText( position[0].ToString() );
		m_TxtSelectedY.SetText( position[2].ToString() );

		return true;
	}

	string GetCurrentPositionName()
	{
		if ( m_LstPositionList.GetSelectedRow() != -1 )
		{
			string position_name;
			m_LstPositionList.GetItemText( m_LstPositionList.GetSelectedRow(), 0, position_name );
			return position_name;
		}

		return "";
	}
}