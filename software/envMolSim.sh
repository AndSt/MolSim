echo 'loading xerces.'
module load xerces/3.1
export CPLUS_INCLUDE_PATH=/lrz/sys/libraries/xerces/3.1/include/:$CPLUS_INCLUDE_PATH

echo 'loading log4cxx.'
export LD_LIBRARY_PATH=$HOME/software/log4cxx/apache-log4cxx-0.10.0/lib:$LD_LIBRARY_PATH
export CPLUS_INCLUDE_PATH=$HOME/software/log4cxx/apache-log4cxx-0.10.0/include/:$CPLUS_INCLUDE_PATH

echo 'loading cppunit.'
export LD_LIBRARY_PATH=$HOME/software/cppunit/cppunit/lib:$LD_LIBRARY_PATH
export CPLUS_INCLUDE_PATH=$HOME/software/cppunit/cppunit/include/:$CPLUS_INCLUDE_PATH

export LIBRARY_PATH=$LIBRARY_PATH:$LD_LIBRARY_PATH
