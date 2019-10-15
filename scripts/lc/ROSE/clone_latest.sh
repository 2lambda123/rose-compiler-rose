#!/bin/bash
# Clones ROSE.
# Calls srun_do and run_and_log as needed.

# For debug:
#set -x

enclosing_directory=`dirname $0`
export ROSE_SCRIPT_DIR=`(cd ${enclosing_directory}; pwd)`
source ${ROSE_SCRIPT_DIR}/declare_install_functions.sh

# Don't actually run:
#export RUN_OR_NOT_EFFORT_ONLY=TRUE

# For manual testing:
#export ROSE_PROJECT_BASE="${HOME}/code/ROSE"

# Uses ROSE_PROJECT_BASE if set, else sets it:
set_main_vars

clone_latest_workspace

