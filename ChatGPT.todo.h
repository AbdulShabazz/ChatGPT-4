th1.
1 + 1 + 1 + 1 = 4

ax2.
2 + 2 = 4

ax3.
1 + 1 = 2

th1.LHSCallGraph_UInt64Map[RouteSource_EnumClass::_rhs] = {3} // th1.UpdatePrimaryKey_LHS(ax3.LHSPrimaryKey_UInt64, ax3.RHSPrimaryKey_UInt64)
th1.LHSCallGraph_UInt64Map[RouteSource_EnumClass::_rhs] = {}
th1.RHSCallGraph_UInt64Map[RouteSource_EnumClass::_lhs] = {2} // th1.UpdatePrimaryKey_RHS(ax2.RHSPrimaryKey_UInt64, ax2.LHSPrimaryKey_UInt64)
th1.RHSCallGraph_UInt64Map[RouteSource_EnumClass::_rhs] = {}

ax2.LHSCallGraph_UInt64Map[RouteSource_EnumClass::_lhs] = {}
ax2.LHSCallGraph_UInt64Map[RouteSource_EnumClass::_rhs] = {3} // ax2.UpdatePrimaryKey_LHS(ax3.LHSPrimaryKey_UInt64, ax3.RHSPrimaryKey_UInt64)
ax2.RHSCallGraph_UInt64Map[RouteSource_EnumClass::_lhs] = {1} // ax2.UpdatePrimaryKey_RHS(ax3.RHSPrimaryKey_UInt64, ax3.LHSPrimaryKey_UInt64)
ax2.RHSCallGraph_UInt64Map[RouteSource_EnumClass::_rhs] = {}

ax3.LHSCallGraph_UInt64Map[RouteSource_EnumClass::_lhs] = {}
ax3.LHSCallGraph_UInt64Map[RouteSource_EnumClass::_rhs] = {}
ax3.RHSCallGraph_UInt64Map[RouteSource_EnumClass::_lhs] = {}
ax3.RHSCallGraph_UInt64Map[RouteSource_EnumClass::_lhs] = {}
