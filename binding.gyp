{
  'targets': [
    {
      'target_name': 'cgns',
      'sources': [
        'src/helper.cc',
        'src/cgns.cc',
        'src/Doc.cc',
        'src/Base.cc',
        'src/Zone.cc',
        'src/Grid.cc',
        'src/Coord.cc',
        'src/Solution.cc'
      ],
      'dependencies': [
      ],
      'include_dirs': [
        '/usr/include',
      ],
      'libraries': [
        '-lcgns',
        '-L/usr/lib',
        '-lhdf5',
        '-L/usr/lib/x86_64-linux-gnu/hdf5/serial/lib'
      ]
    }
  ]
}
