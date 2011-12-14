/*=========================================================================

  Program:   ParaView
  Module:    $RCSfile$

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkSMViewLayout - vtkSMViewLayout is used by ParaView to layout
// multiple views in a 2D KD-Tree layout.
// .SECTION Description
// 

#ifndef __vtkSMViewLayout_h
#define __vtkSMViewLayout_h

#include "vtkSMRemoteObject.h"

class vtkSMProxy;

class VTK_EXPORT vtkSMViewLayout : public vtkSMRemoteObject
{
public:
  static vtkSMViewLayout* New();
  vtkTypeMacro(vtkSMViewLayout, vtkSMRemoteObject);
  void PrintSelf(ostream& os, vtkIndent indent);

  enum Direction
    {
    NONE,
    VERTICAL,
    HORIZONTAL
    };

  // Description:
  // Split a frame at the given \c location. Location must point to an existing cell
  // that's not split. If the location does not exist or is already split, then
  // returns 0, to indicate failure. Otherwise returns the index of the left (or
  // top) child node. The index for the sibling can be computed as (ret_val +
  // 1). \c fraction indicates a value in the range [0.0, 1.0] at which the cell
  // is split. If a View is set at the given location, it will be moved to the
  // left (or top) child after the split.
  unsigned int Split(unsigned int location, int direction, double fraction);
  unsigned int SplitVertical(unsigned int location, double fraction)
    { return this->Split(location, VERTICAL, fraction); }
  unsigned int SplitHorizontal(unsigned int location, double fraction)
    { return this->Split(location, HORIZONTAL, fraction); }

  // Description:
  // Assign a view at a particular location. Note that the view's position may
  // be changed by Split() calls. Returns true on success.
  bool AssignView(unsigned int location, vtkSMProxy* view);

  // Description:
  // Removes a view. Returns the location of the cell emptied by the view.
  unsigned int RemoveView(vtkSMProxy* view);

  // Description:
  // Collapses a cell. Only leaf cells without any assigned views can be collapsed.
  // If the cell has a sibling, then that sibling is assigned to the parent
  // node and the sibling cell is destroyed as well. Returns true on success,
  // else false.
  bool Collape(unsigned int location);

  bool IsSplitCell(unsigned int location);
  Direction GetSplitDirection(unsigned int location);
  unsigned int GetFirstChild(unsigned int location)
    { return 2*location + 1; }
  unsigned int GetSecondChild(unsigned int location)
    { return 2*location + 2; }
  vtkSMProxy* GetView(unsigned int location);

//BTX
protected:
  vtkSMViewLayout();
  ~vtkSMViewLayout();

private:
  vtkSMViewLayout(const vtkSMViewLayout&); // Not implemented
  void operator=(const vtkSMViewLayout&); // Not implemented

  class vtkInternals;
  vtkInternals* Internals;
//ETX
};

#endif
