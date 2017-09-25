{
  'targets': [
    {
      'target_name': 'cgns',
      'sources': [
        'src/helper.cc',
        'src/cgns.cc',
        'src/Doc.cc'
      ],
      'dependencies': [
      ],
      'include_dirs': [
        '/usr/local/include'
      ],
      'libraries': [
        '-lcgns',
        '-L/usr/local/lib'
      ]
    }
  ]
}