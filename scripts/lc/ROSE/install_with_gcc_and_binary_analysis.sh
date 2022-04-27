#!/bin/bash
# Configure, make, and install ROSE with gcc and binary analysis enabled.  
# Run after clone_and_preconfigure.sh.
# Calls srun_do and run_and_log as needed.

# For debug:
#set -x

enclosing_directory=`dirname $0`
export ROSE_SCRIPT_DIR=`(cd ${enclosing_directory}; pwd)`
source ${ROSE_SCRIPT_DIR}/declare_install_functions.sh

# Don't actually run:
#export RUN_OR_NOT_EFFORT_ONLY=TRUE

# For manual testing:
#export ROSE_BUILD_BASE="${HOME}/code/ROSE"

# Uses ROSE_BUILD_BASE if set, else sets it:
set_main_vars
use_latest_existing_workspace
setup_gcc_compiler_with_binary_analysis
setup_boost
print_rose_vars
do_gcc_configure_with_binary_analysis
make_and_install
