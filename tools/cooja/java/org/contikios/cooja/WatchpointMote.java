/*
 * Copyright (c) 2009, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

package org.contikios.cooja;

import java.io.File;

/**
 * @author Fredrik Osterlind
 */
public interface WatchpointMote extends Mote {

  interface WatchpointListener {
    void watchpointTriggered(Watchpoint watchpoint);
    void watchpointsChanged();
  }

  /**
   * Adds a breakpoint listener.
   * The listener will be notified when breakpoints are added, removed or triggered.
   *
   * @param listener Action listener
   */
  void addWatchpointListener(WatchpointListener listener);

  /**
   * Removes previously registered listener.
   *
   * @param listener Listeners
   */
  void removeWatchpointListener(WatchpointListener listener);

  /**
   * @return All registered listeners
   */
  WatchpointListener[] getWatchpointListeners();

  Watchpoint addBreakpoint(long address, File codeFile, int lineNr);
  void removeBreakpoint(Watchpoint watchpoint);
  Watchpoint[] getBreakpoints();

  boolean breakpointExists(long address);
  boolean breakpointExists(File file, int lineNr);
}
