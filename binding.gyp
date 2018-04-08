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
        '/usr/local/include',
        '/usr/include'
      ],
      'libraries': [
        '-lcgns',
        '-lhdf5',
        '-L/usr/local/lib',
        '-L/usr/lib',
        '-L/usr/lib/x86_64-linux-gnu/hdf5/serial'
      ]
    }
  ]
}
